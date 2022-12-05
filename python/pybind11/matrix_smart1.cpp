#include "matrix_smart.hpp"
#include <pybind11/pybind11.h>

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
                           static_cast< DCMatrix&(DCMatrix::*)( const DCMatrix &) > // select the assignment operator
                            (&DCMatrix::operator=)
                            )
            ;

}
