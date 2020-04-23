/* 14 Younhong Ko, sjgkfkadk@hanmail.net
Implementation date: 09/29/16
This program is to read and add all numbers from the text file.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	string fileName = " ";  // file name
	ifstream textFile;	    // Data file
	char curChar = ' ';     // current letter
	char preChar = ' ';	    // previous letter
	float temp = 0;			// temp var to save number
	float sum = 0;			// sum of data

	cout << "Enter the name of file: ";
	cin >> fileName;

	textFile.open(fileName.c_str());
	
	if (!textFile) {
		cout << "Can't open file" << endl;
		exit(1);
	}

	textFile.get(curChar);
	while (textFile) {
		if (isdigit(curChar)) {
			if (isdigit(preChar)) {
				temp = temp * 10 + curChar;
			}
			else {
				if (preChar == '.') {
					sum = sum + curChar / 10;
				}
				else if (preChar == ',') {
					temp = temp * 10 + curChar;
				}
				else {
					temp = curChar;
				}
			}
		}
		else {
			if (curChar != ',') {
				sum = sum + temp;
				temp = 0;
			}
		}
		preChar = curChar;
		textFile.get(curChar);
	}

	cout << "The sum is " << sum << endl;

	textFile.close();

	return 0;
}