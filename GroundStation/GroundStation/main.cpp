#include <python3.5/Python.h>
#include <wiringPi.h>

int main(void) {


	// RUN THERMOCOUPLE PYTHON SCRIPT
	Py_Initialize();

	PyObject *obj = Py_BuildValue("s", "thermocouple_31856.py");
	FILE *file = _Py_fopen_obj(obj, "r+");
	if (file != NULL) {
		PyRun_SimpleFile(file, "thermocouple_31856.py");
	}
	Py_Finalize();


	
	return 0;
}