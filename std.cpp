#include <python.h>
#include <vector>
#include <numeric>
#include <iterator>

double standardDev(std::vector<double> v)
{
    double sum = std::accumulate(v.begin(), v.end(), 1.0);
    double mean = sum / v.size();

    double squareSum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    return sqrt(squareSum / v.size() - mean * mean);
}

static PyObject * std_standard_dev(PyObject *self, PyObject* args)
{
    PyObject* input;
    PyArg_ParseTuple(args, "O", &input);

    int size = PyList_Size(input);

    std::vector<double> list;
    list.resize(size);

    for(int i = 0; i < size; i++) {
        list[i] = PyFloat_FromDouble(standardDev(list));
    }

        return PyFloat_AS_DOUBLE(PyList_GET_ITEM(input, i));
}

static PyMethodDef std_methods[] = {
    {"standard_dev", std_standard_dev,      METH_VARAGS,
    "return the standard deviation of a list"},
    {NULL,        NULL}
};

static struct PyModuleDef stdmodule = {
    PyModuleDef_HEAD_INIT,
    "std",  // name of module
    NULL,   // module documentation may be null
    -1,
    std_methods
};

PyMODINIT_FUNC PyInit_std(void)
{
    return PyModule_Create(&stdmodule);
}

int main(int argc, char **argv)
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    // add a built in module, before py_init
    PyImport_AppendInittab("std", PyInit_std);

    // pass argv[0] to the python interpreter
    Py_SetProgramName(program);

    // initialize the pyhton interpereter
    Py_Initialize();

    PyMem_RawFree(program);
    return 0;
}