// DLL.cpp : Defines the exported functions for the DLL application.

#include "windows.h"
#include <iostream>
#include <sstream>
#include <string>

#define ASEXPORT
#include "filter.h"  // header file inside SLL project

using namespace std;

// Function used to filter data
int Filter(int data[], int count, const WCHAR* parameterString)
{
	wstring ws(parameterString);
	string filter(ws.begin(), ws.end()); 	// Convert WCHAR string into a normal string
	int spaceIndex = 0; // index for position of the space in the filter

	// Set range limits of filter

	// Find the space index
	for (int i = 0; i < filter.length(); i++)
	{
		if (filter[i] == ' ')
		{
			spaceIndex = i;
			break; // Break out of loop when found
		}
	} // End of for loop

	// Seperate the two strings into seperate data
	// Set the upper and lower limits of the data range
	int lowerLimit = stoi(filter.substr(0, spaceIndex));
	int upperLimit = stoi(filter.substr(spaceIndex + 1, filter.length() - spaceIndex + 1));

	for (int i = 0; i < count; i++) // Convert the data using the data limits
	{
		if      (data[i] < lowerLimit) data[i] = lowerLimit;
		else if (data[i] > upperLimit) data[i] = upperLimit;

	} // End of for loop

	return Success;

} // End of Filter function 


