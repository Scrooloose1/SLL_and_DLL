// CO2411: Software Engineering Practices (2018/19)
// Assignment: Using Libraries and Debugging
// Last Edited: 01/08/2019

#include <windows.h>
#include <iostream>
#include <string>
#include "filter.h"  // This is the header file located in the SLL project

using namespace std;

const WCHAR* INPUT_FILE  = L"dataInFile.txt";    // Data Input File
const WCHAR* OUTPUT_FILE = L"dataOutFile.txt";   // Data Output File
const WCHAR* DLL_NAME    = L"DLL";
const WCHAR* FILTER_RULE = L"-10 10";

int MeasurementsData[MAX_DATA]; // Array to hold data
int DataCount = 0;              // Amount of items returned by the read in function
int status = 0;                 // Status of UseFilter function

// Function to display errors
void DisplayErrors(int errorCode)
{
	cout << "\n Error code: " << errorCode;
	switch (errorCode)
	{
	case Failure:
		cout << "\n Failure - Input text file not found.";
		break;
	case DllNotFound:
		cout << "\n DLL not found";
		break;
	case DllInvalidFormat:
		cout << "\n DLL is an Invalid Format";
		break;
	case UnknownError:
		cout << "\n An unknown Error has occured";
		break;
	case InvalidParameters:
		cout << "\n Invalid Parameters";
		break;
	} // End of switch statment

} // End of DisplayErrors function


// Main Function
int main() 
{
	cout << "\n\n CO2411: Software Engineering Practices";
	cout << "\n Program started:";
	cout << "\n\n Reading in data file...";

	status = UnknownError; // Set starter Status

	// Call the LoadMeasurements function in SLL
	DataCount = LoadMeasurements(INPUT_FILE, MeasurementsData, MAX_DATA);

	if (DataCount > 0) // If no error code has been produced
	{
		// Output number of data items stated in text file
		cout << "\n\n Number of items in data file : " << DataCount << "\n\n";

		// Output data items
		for (int i = 0; i < DataCount; i++)
		{
			cout << " Data item " << i + 1 << " : " << MeasurementsData[i] << endl;

		} // End of for loop

		// Call the UseFilter function in the SLL
		status = UseFilter(DLL_NAME, MeasurementsData, DataCount, FILTER_RULE);

		if (status == Success) // If data items have been converted sucessfully
		{
			cout << "\n\n Data has been sucessfully filtered";
			cout << "\n\n Converted data:\n\n";

			// Display converted data items
			for (int i = 0; i < DataCount; i++)
			{
				cout << " Data item " << i + 1 << " : " << MeasurementsData[i] << endl;

			} // End of for loop

			// Call the SaveMeasurements function in the SLL
			// Output the data to a text file
			status = SaveMeasurements(OUTPUT_FILE, MeasurementsData, DataCount);

			if (status == Success) // Check if data has been outputted sucessfully
			{
				wstring ws(OUTPUT_FILE);
				string  outputFileName(ws.begin(), ws.end()); // Convert WChar string to normal string

				cout << "\n Data has been sucessfully output to the file " << outputFileName << "\n";

			} // end of if statment
		}
		else
		{
			DisplayErrors(DataCount); // If not, display correct error message

		} // End of else-if statment
	}
	else
	{
		DisplayErrors(DataCount); // display correct error message

	} // End of else-if statment

	cout << "\n Program finished.\n";

	cout << " Press Enter to quit...";
	getchar(); // Pause until enter is pressed

	return 0;

} // End of main Function
