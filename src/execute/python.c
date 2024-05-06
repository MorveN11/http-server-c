#include </usr/include/python3.12/Python.h>

char *execute_python_code(const char *python_code) {
    Py_Initialize();

    PyRun_SimpleString("import sys\n"
                       "from io import StringIO\n"
                       "sys.stdout = mystdout = StringIO()");

    int result = PyRun_SimpleString(python_code);

    if (result != 0) {
        PyErr_Print();
        Py_Finalize();
        return NULL;
    }

    PyObject *sys_module = PyImport_ImportModule("sys");
    PyObject *mystdout = PyObject_GetAttrString(sys_module, "stdout");
    PyObject *output_pyobj = PyObject_CallMethod(mystdout, "getvalue", NULL);

    const char *output_cstr = PyUnicode_AsUTF8(output_pyobj);
    char *output = strdup(output_cstr);

    Py_DECREF(output_pyobj);
    Py_DECREF(mystdout);
    Py_DECREF(sys_module);

    Py_Finalize();

    return output;
}
