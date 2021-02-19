#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "filter.h"

using namespace std;

// Function to load in measurements from the text file
int LoadMeasurements(const WCHAR* inputFile, int data[], int maxSize)
{
	// Get first amount - Number of data items
	string line;
	int num = 0;
	int numOfLines = 0;
	ifstream inFile;
	inFile.open(inputFile);

	if (inFile.is_open()) // Is the file open?i thi
	{
		inFile >> line; // Read in first line

		// Check if the first number read in is a int or a string
		if (istringstream(line) >> num) // If an integer
		{
			// Check if num is in range
			if ((num > 0) && (num <= MAX_NUM_DATA_ITEMS))
			{
				// Count number of data lines in text file
				inFile.clear();
				inFile.seekg(0, ios::beg); // Reset reading of infile

				while (getline(inFile, line)) // read in line by line
				{
					if (line.empty() == false)
					{
						numOfLines++;
					}

				} // End of while loop

				numOfLines -= 1; // Remove first line from total

				// Check if number of lines of data matches Number of data items
				if (num != numOfLines)
				{
					inFile.close();
					return InvalidParameters; // If not return error

				} // End of if statment
				
				inFile.clear();
				inFile.seekg(0, ios::beg); // Reset reading of infile
				getline(inFile, line);     // Skips first line

				// Read in data
				for (int i = 0; i < numOfLines; i++)
				{
					getline(inFile, line);
					if (istringstream(line) >> num) // If an integer
					{
						data[i] = num;
					}
					else // if item read in is not an integer (like a letter or symbol)
					{
						inFile.close();
						return InvalidParameters;

					} // End of if-else statment
				}
			}
			else // Is the number of items out of range?
			{
				inFile.close();
				return InvalidParameters; // Return error

			} // End of if-else statment

		}
		else // Does the text file contain string data instead of integers?
		{
			inFile.close();
			return InvalidParameters; // Return error

		} // End of if-else statment

	} 
	else // If no text file can be found
	{
		return Failure; // Return error code
	}
		
	//#ifdef _DEBUG 
	//cout << "\n\n";
	//for (int i = 0; i < numOfLines; i++)
	//{
	//	cout << " Data item " << i << " : " << data[i] << endl;
	//}
	//#endif

	return numOfLines; // Return nuber of data items if successful



} // End of LoadMeasurements function

// Function to Use the filter on the data items read in from the text file
int UseFilter(const WCHAR* dllName, int data[], int count, const WCHAR* parameterString)
{
	int statusCode = UnknownError; // Set starter error

	HINSTANCE dllHandle = LoadLibrary(dllName); // Get a handle to the DLL Module

	if (dllHandle != NULL)     // If the handle is valid, get the function address
	{
		FuncPFilter dllFilterFunction = (FuncPFilter)GetProcAddress(dllHandle, "Filter");

		if (dllFilterFunction != NULL) // If function address is valid, call the function.
		{
			statusCode = (dllFilterFunction)(data, count, parameterString);
		}
		else
		{
			return DllInvalidFormat; // Else return error

		} // End of if-else statment

		BOOL dllFreeResult = FreeLibrary(dllHandle); // Free the DLL module

		if (!dllFreeResult)
		{
			return UnknownError;

		} // End of if statment
	}
	else
	{
		return DllNotFound; // Return dll not found

	} // End of if-else statment

	return statusCode; // 0 if found, or error code if not

} // End of UseFilter function

// Function to Use the filter on the data items read in from the text file
int SaveMeasurements(const WCHAR* outputFile, int data[], int maxSize)
{
	ofstream outFile;
	outFile.open(outputFile);  // Open Output file

	if (!outFile.is_open()) 	// Check if the file is not open
	{
		#ifdef _DEBUG // will only output this in Debug mode
		cout << "Unable to open the output file.\n\n";
		#endif

		return UnknownError; // Return error code

	} // ENd of if statment

	for (int i = 0; i < maxSize; i++)
	{
		outFile << data[i] << "\n"; // Output data to text file

	} // End of for loop

	outFile.close(); // Close output file

	return Success; 

} // End of SaveMeasurements function