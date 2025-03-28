#define PY_SSIZE_T_CLEAN
#include <Python.h>

PyObject* add_columns(PyObject* column1,PyObject* column2)
{
    int column_size=PyList_Size(column1);
    float final_column[column_size];
    for(int i=0; i<column_size;i++)
    {
        PyObject*  item1=PyList_GetItem(column1,i);
        PyObject*  item2=PyList_GetItem(column2,i);
        if (!PyFloat_Check(item1) && !PyLong_Check(item1) && !PyFloat_Check(item2) && !PyLong_Check(item2)) {  // Ensure it's a number
            PyErr_SetString(PyExc_TypeError, "List must contain only numbers");
            return NULL;}
       
        final_column[i]=PyFloat_AsDouble(item1)+PyFloat_AsDouble(item2);
    }
    PyObject* py_list=PyList_New(column_size);
    for(int i=0; i<column_size;i++)
    {
        PyObject* item = PyFloat_FromDouble(final_column[i]);
        PyList_SetItem(py_list,i,item);
    }
    return py_list;

}

static PyObject* sum_array(PyObject* self,PyObject* args)
{
    PyObject* arr1;
    PyObject* arr2;
    if (!PyArg_ParseTuple(args, "O!O!"/*Symbol for expecting a list*/, &PyList_Type, &arr1,&PyList_Type, &arr2)) {
        return NULL;  // Return NULL if parsing fails
    }
    int list1_row_size=PyList_Size(arr1);
    int list2_row_size=PyList_Size(arr2);
    if(list1_row_size != list2_row_size)
    {
        PyErr_SetString(PyExc_TypeError,"The 1D array must have the same number of values");
        return NULL;

    }
     
    PyObject* final_array=PyList_New(list1_row_size);

    for (int i=0;i<list1_row_size;i++)
    {
        PyObject* column1 =PyList_GetItem(arr1,i);
        PyObject* column2=PyList_GetItem(arr2,i);
        PyList_SetItem(final_array,i,add_columns(column1,column2));



    }
    return final_array;
}
static PyMethodDef MyMethods[] = {
    {"sum_array", sum_array, METH_VARARGS, "Sum of two different arrays"},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define module
static struct PyModuleDef arraymodule = {
    PyModuleDef_HEAD_INIT,
    "dpy",
    "A module for handling arrays",
    -1,
    MyMethods
};

// Module initialization
PyMODINIT_FUNC PyInit_dpy(void) {
    return PyModule_Create(&arraymodule);
}