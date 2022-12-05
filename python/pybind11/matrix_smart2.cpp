#include "matrix_smart.hpp"
#include "pybind11/cast.h"
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
            ;

}
