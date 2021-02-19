#ifndef H_FILTER
#define H_FILTER

const int Success           = 0;
const int Failure           = -1;
const int DllNotFound       = -2;   // Unable to find DLL to import
const int DllInvalidFormat  = -3;   // Unable to find import function in the dll
const int UnknownError      = -4;   // An unknown error has occured
const int InvalidParameters = -5;   // Invalid parameters have been used

const int MAX_DATA           = 1000;  // The maximum size of the array for loading data 
const int MAX_NUM_DATA_ITEMS = 100;   // Number of data items listed in the text file

int LoadMeasurements(const WCHAR* inputFile, int data[], int maxSize);
int UseFilter(const WCHAR* dllName, int data[], int count, const WCHAR* parameterString);
int SaveMeasurements(const WCHAR* outputFile, int data[], int maxSize);

typedef int(*FuncPFilter)(int[], int, const WCHAR*);  // Function pointer to filter inside the DLL

#ifndef ASEXPORT
#define DLLIMPORTOREXPORT dllimport
#else
#define DLLIMPORTOREXPORT dllexport

#endif

#ifdef __cplusplus  // If used by C++ code, 
extern "C" {        // Export C interface (avoid name mangling)
#endif

	_declspec(DLLIMPORTOREXPORT) int Filter(int data[], int count, const WCHAR* parameterString);

#ifdef __cplusplus  // If used by C++ code
}                   // End extern "C"
#endif

#endif