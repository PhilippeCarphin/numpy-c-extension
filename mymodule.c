#include <Python.h>
// This macro will prevent us from using things that are deprecated
// from the point of view of the specified version
// For example, looking in the header files, because we are specifying
// version 1.19, the function PyArray_XDECREF_ERR(PyArrayObject *arr)
// will not be declared for us:
//     #if !defined(NPY_NO_DEPRECATED_API) || \
//         (NPY_NO_DEPRECATED_API < NPY_1_14_API_VERSION)
//     static NPY_INLINE void
//     PyArray_XDECREF_ERR(PyArrayObject *arr
#define NPY_NO_DEPRECATED_API NPY_1_19_API_VERSION
// I would have included "numpy/ndarrayobject.h" because that's what I want
// to work with but I happened to look at ndarrayobject.h and it turns out
// that it says "DO NOT INCLUDE THIS FILE DIRECTLY" at the top.
#include <numpy/arrayobject.h>
#include <stdio.h>
PyObject * make_array_impl(int array_size){
    
}

PyObject *make_array(PyObject *self, PyObject *args){

    int array_size;

    printf("%s\n", __PRETTY_FUNCTION__);

    if(!PyArg_ParseTuple(args, "ifs", &array_size)){
        return NULL;
    }

    const char *result = my_func_impl(array_size);

    return Py_BuildValue("s", result);
}

static PyMethodDef mymodule_method_def[] = {
    {
        .ml_name = "make_array",
        .ml_meth = (PyCFunction)make_array,
        .ml_flags = METH_VARARGS,
        .ml_doc = "Documentation for make_array"
    },
    {NULL, NULL, 0, NULL}
};

static PyModuleDef mymodule_def = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "npextension",
    .m_doc = "Documentation for mymodule",
    .m_size = -1,
    .m_methods = mymodule_method_def,
};

PyMODINIT_FUNC
PyInit_npextension(void)
{
    printf("%s\n", __PRETTY_FUNCTION__);
    PyObject *module = PyModule_Create(&mymodule_def);

    if (module == NULL){
        printf("%s module returned by PyModule_Create() is NULL\n", __PRETTY_FUNCTION__);
        return NULL;
    }

    import_array();

    return module;
}