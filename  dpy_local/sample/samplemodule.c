#define PY_SSIZE_T_CLEAN //function correctly handles Py_ssize_t values (Do a detailed search later regarding what this actualls means)

#include <Python.h>

// C function to add two numbers
static PyObject* add(PyObject* self, PyObject* args) {
    int a, b, result;
    
    // Parse Python arguments (expecting two integers)
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) 
    /*
    PyArg_ParseTuple parses the python arguments into C int's
    PyObject* args is the python arguments 
    All python arguments in C are referred to as PyObject type 
    (ii) dentoes that PyArg_ParseTuple expects two integers
    */
    {
        return NULL;  // Return NULL on error
    }

    result = a + b;

    // Return result as a Python integer
    return PyLong_FromLong(result);
    /*
    Pylong_FromLong converts an C data type back into python data type
    */
}

// Define module methods
static PyMethodDef MyModuleMethods[] = {
    {"add" // This is what the function will be called in python 
    , add, // This is the name of the function in C 
     METH_VARARGS,// This is used for Positional arguments
     // use METH_KEYWORDS if you are using keyword arguments
     "Function to add two numbers"},
    {NULL, NULL, 0, NULL}  // Sentinel to indicate the end of the method array
};

// Define module
static struct PyModuleDef addmodule = {
    PyModuleDef_HEAD_INIT,
    "add_module",  // Module name
    "A simple C extension module",  // Module docstring
    -1,  // Module state size (-1 means global state)
    MyModuleMethods
};

// Module initialization function
PyMODINIT_FUNC PyInit_add_module(void) {
    return PyModule_Create(&addmodule);
}
