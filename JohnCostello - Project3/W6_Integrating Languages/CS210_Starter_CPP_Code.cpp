#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// call a Python function by name, function should have no arguments and no return value
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code"); 
	// !!! PythonCode => CS210_Starter_PY_Code this is in 3 places
	// !!! create CS210_Starter_PY_Code.py under Release folder
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

// call Python function that uses a search term passed and returns the corresponding quantity found in the input file
int getItemQuantity(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

// helper function for reading the input file to a vector
vector<string> readInputFile() {
	vector<string> inputVector;

	// open file, exit if there is an error
	ifstream inFile;
	inFile.open("Input.txt");
	if (!inFile) {
		cerr << "Unable to open input file." << endl;
		exit(1);
	}

	// read each line and store the line in the vector
	string item;
	while (inFile >> item) {
		inputVector.push_back(item);
	}

	inFile.close();

	return inputVector;
}

// function to print histogram based on the frequency.dat file made in Python
void PrintHistogram() {
	ifstream inFile;

	// open the frequency file, exit if an error is thrown
	inFile.open("frequency.dat");
	if (!inFile) {
		cerr << "Unable to open frequency file." << endl;
		exit(1);
	}

	string item = "";
	string name = "";
	string quantity = "";
	// read the name and number from each line and store in local variables
	while (inFile >> name >> quantity) {
		cout << name << " ";

		// add a * to each line, loop until the star count matches the quantity
		for (int i = 0; i < stoi(quantity); i++) {
			cout << "*";
		}

		cout << endl;
	}

	inFile.close();
}

int main()
{
	int menuSelection = -1;
	int userInput = -1;
	int itemQuatity = -1;
	string searchTerm = "";
	// call function to read in input from text file
	vector<string> input = readInputFile();

	while (menuSelection != 4)
	{
		// display menu
		cout << "1: Print a list of all items sold, and the amount of each sold" << endl;
		cout << "2: Print how much of a single item was sold" << endl;
		cout << "3: Print a histogram showing how much of each item was sold" << endl;
		cout << "4: Exit" << endl;
		cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;

		cin >> menuSelection;

		// check one of the 4 ints was selected
		while (menuSelection != 1 && menuSelection != 2 && menuSelection != 3 && menuSelection != 4) {
			cout << "Invalid input. Enter your selection as a number 1, 2, 3, or 4." << endl;
			cin.clear();
			cin.ignore();
			cin >> menuSelection;
		}

		// execute function based on user selection
		switch (menuSelection)
		{
		case 1:
			cout << endl;
			
			// call function to display sales numbers
			CallProcedure("PrintItems");
			
			cout << endl;

			break;
		case 2:
			cout << "Please input the item you would like to view results for: " << endl;
			cin.clear();
			cin.ignore();
			cin >> searchTerm;
			
			// call function to display sales numbers for 1 item
			itemQuatity = getItemQuantity("GetItemQuantity", searchTerm);

			cout << endl;
			cout << searchTerm << ": " << itemQuatity << endl;
			cout << endl;
			
			break;
		case 3:
			cout << endl;

			// call function to make .dat file
			CallProcedure("PrintHistograms");

			// call function to print histogram
			PrintHistogram();

			cout << endl;
			break;
		case 4:
			break;
		default:
			cout << "Invalid selection." << endl;
			break;
		}
	}

	return 0;
}