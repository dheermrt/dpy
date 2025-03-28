#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject* sum_array(PyObject* self, PyObject* args)
{ 
    PyObject* arr1;
    PyObject* arr2;
     
     if (!PyArg_ParseTuple(args, "O!O!"/*Symbol for expecting a list*/, &PyList_Type, &arr1,&PyList_Type, &arr2)) {
        return NULL;  // Return NULL if parsing fails
    }
    int list1_size=PyList_Size(arr1);
    int list2_size=PyList_Size(arr2);
    if(list1_size!=list2_size)
    {
        PyErr_SetString(PyExc_TypeError,"The 1D array must have the same number of values");
        return NULL;

    }
    float finalarray[list1_size];
    for(int i=0; i<list1_size;i++)
    {
        PyObject*  item1=PyList_GetItem(arr1,i);
        PyObject*  item2=PyList_GetItem(arr2,i);
        if (!PyFloat_Check(item1) && !PyLong_Check(item1) && !PyFloat_Check(item2) && !PyLong_Check(item2)) {  // Ensure it's a number
            PyErr_SetString(PyExc_TypeError, "List must contain only numbers");
            return NULL;}
       
        finalarray[i]=PyFloat_AsDouble(item1)+PyFloat_AsDouble(item2);
    }
    PyObject* py_list=PyList_New(list1_size);
    for(int i=0; i<list1_size;i++)
    {
        PyObject* item = PyFloat_FromDouble(finalarray[i]);
        PyList_SetItem(py_list,i,item);
    }
    return py_list;
}
// Define module methods
static PyMethodDef MyMethods[] = {
    {"sum_array", sum_array, METH_VARARGS, "Sum of two different arrays"},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define module
static struct PyModuleDef arraymodule = {
    PyModuleDef_HEAD_INIT,
    "array_module",
    "A module for handling arrays",
    -1,
    MyMethods
};

// Module initialization
PyMODINIT_FUNC PyInit_array_module(void) {
    return PyModule_Create(&arraymodule);
}

    



    

