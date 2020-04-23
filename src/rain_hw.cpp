/* 14 Younhong Ko, sjgkfkadk@hanmail.net
Implementation date: 09/11/16
This code is to read data from file(rainFile) and get results such as
average rainfall, max rainfall, and number of days that rained more than limit. */

#include <iostream>
#include <fstream>
using namespace std;

float GetInches(ifstream& rainFile, int numberOfDays); 
// Function returns the total inches of rain
float GetMax(ifstream& rainFile, int numberOfDays);
// Function returns the maximum rain fall
int Count(ifstream& rainFile, int numberOfDays, float threshold);
// Function returns the number of days that rained more than threshold

int main()
{
	ifstream  rainFile;		// data file
	float average = 0.0;	// average rainfall
	float totalRain = 0.0;	// Total accumulated rain
	int numberOfDays = 0;	// Number of days in calculation
	char option = ' ';		// choice of result
	float threshold = 0.0;	// limit of rainfall
	int countDay = 0;		// number of days that rained more than threshold
	float maxRain = 0.0;	// maximum rainfall
	char fileName[60] = " "; // name of file

	cout << "Input the file name: ";
	cin >> fileName;
	rainFile.open(fileName);	
	rainFile >> numberOfDays;

	cout << "What do you want? Press a(average), x(max), or c(count): ";
	cin >> option;
  
	while (option != 'q') {
		if (numberOfDays == 0) {
			cout << "No days to check rain";
		}
		else {
			if (option == 'a') {
				totalRain = GetInches(rainFile, numberOfDays);
				if (totalRain == 0.0) {
					cout << "There was no rain during this period." << endl;
				}
				average = totalRain / numberOfDays;
				cout << "The average rain fall over " << numberOfDays << " days is " << average << endl;
			}
			else if (option == 'x') {
				maxRain = GetMax(rainFile, numberOfDays);
				cout << "The max rain fall is " << maxRain << endl;
			}
			else if (option == 'c') {
				cout << "Enter the threshold: ";
				cin >> threshold;
				countDay = Count(rainFile, numberOfDays, threshold);
				cout << "The number of days with more than " << threshold << " rain fall is " << countDay << endl;
			}
			else {
				cout << "Wrong choice!!" << endl;
			}
		}
		rainFile.close();
		cout << "Input the file name: ";
		cin >> fileName;
		rainFile.open(fileName);
		rainFile >> numberOfDays;
		cout << "What do you want? Press a(average), x(max), or c(count): ";
		cin >> option;
	}

	rainFile.close();
	cout << "Good Bye!!" << endl;
	
	return 0;
}

float GetInches(ifstream& rainFile, int numberOfDays)
{
	float inches;         // Day's worth of rain
	int counter = 1;      // Loop control variable
	float totalRain = 0.0;

	while (counter <= numberOfDays) {
		rainFile >> inches;
		totalRain = totalRain + inches;
		counter++;
	}

	return totalRain;
}

float GetMax(ifstream& rainFile, int numberOfDays)
{
	float inches;
	int counter = 1;
	float maxRain = 0.0;

	while (counter <= numberOfDays) {
		rainFile >> inches;
		if (maxRain <= inches) {
			maxRain = inches;
		}
		counter++;
	}

	return maxRain;
}

int Count(ifstream& rainFile, int numberOfDays, float threshold)
{
	float inches;
	int counter = 1;
	int countDay = 0;

	while (counter <= numberOfDays) {
		rainFile >> inches;
		if (inches > threshold) {
			countDay++;
		}
		counter++;
	}
	
	return countDay;
}