#include "matrix_smart.hpp"
#include "pybind11/cast.h"
#include <cstring>
#include <memory>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <stdexcept>

PYBIND11_MODULE(matrix_smart, m) {
    m.doc() = "This module uses the c++ code to perform simple matrix multiplications"; // optional mdule docstring

    m.def("test_func", &old_main, "execute old main code");
    using DCMatrix = CMatrix<double>;
    pybind11::class_<DCMatrix > (m, "CMatrix")
	    .def(pybind11::init<>())
	    .def("read_from_file",&DCMatrix::read_from_file)
	    .def("print_to_file",&DCMatrix::print_to_file)
	    .def("multiply",&DCMatrix::operator*)
	    .def("assign",
			   static_cast< DCMatrix&(DCMatrix::*)( const DCMatrix &) >
			    (&DCMatrix::operator=)
			    )
	    .def("get_data", [](const DCMatrix & d)
	        {
		   //allocate copy of matrix data and pass it to python domain
		   //Python decides when to destroy the object.
		   //The data is completely given to the python world
		   
		   if (d.size <=0 ) {
		      throw std::runtime_error("matrix is empty");
		   }
		   auto * python_data = new double[d.size*d.size];
		   std::memcpy(python_data,d.data.get(),sizeof(double)*d.size*d.size);

		   //little routine that is called when
		   // the object is collected by the garbage collector
		   pybind11::capsule free_when_done(python_data, [] (void * pointer) {
		       std::cout << "freeing memory @ " << pointer <<std::endl;
		       delete [] reinterpret_cast<double*>(pointer);
		   });

		   return pybind11::array_t<double>( // array_t is in pybind11/numpy.h
	               {{d.size,d.size}},//shape
		       {d.size*sizeof(double),sizeof(double)}, //stride
		       python_data,
		       free_when_done
		   );

	        }
	       )
            .def("set_data",[](DCMatrix &d, const pybind11::buffer numpy_matrix)
	        {
		   //get info of python array
		   pybind11::buffer_info info{numpy_matrix.request()};
		   //check that we are dealing with an array of double
		   if (info.format != pybind11::format_descriptor<double>::format()) {
		      throw std::runtime_error("we can accept only a matrix made with C double type");
		   }
		   //sanity check
		   if (info.ndim != 2) {
		       throw std::runtime_error("dimension of array must be 2");
		   }
		   if (info.shape[0] != info.shape[1]){
		       throw std::runtime_error("we implemented only square matrices, sorry");
		   }
		   if (info.shape[0]<=0) {
		      throw std::runtime_error("dimension of the matrix is zero");
		   }
		   // to simplyfy the logic, implement only contiguous arrays. Check that the array is contiguous
		   ssize_t stride=sizeof(double);
		   for (int i=info.ndim-1;i>=0;--i){
       	              if (info.strides[i] != stride) {
		         throw std::runtime_error("sorry, we don't support non contiguous matrices");
		      }
		      stride *= info.shape[i];
		   }

		   //all sanity checks are passed, copy the data
                   d = DCMatrix(info.shape[0]); //use assignment to not write other code...
		   std::memcpy(d.data.get(),info.ptr,sizeof(double)*info.shape[0]*info.shape[1]);
                   //now c++ is responsable of this data (managed by the smart pointer)
	        }
	       )
	    ;

}

