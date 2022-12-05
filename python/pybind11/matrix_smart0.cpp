#include "matrix_smart.hpp"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(matrix_smart, m) {
    m.doc() = "This module uses the c++ code to perform simple matrix multiplications"; // optional mdule docstring

    m.def("test_func", &old_main, "execute old main code");

}

