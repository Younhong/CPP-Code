/* 14 Younhong Ko, sjgkfkadk@hanmail.net
Implementation date: 10/09/16
This program is to read text file and map file, and change text file's words based on map file.
From map file, which has format of 'A: B'. find all 'A's in text file and change it to 'B'.
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void replaceWord(string& txt, string map1, string map2);

int main() {
	string textFileName = " ";	// text file name
	string mapFileName = " ";	// map file name
	ifstream textFile;			// Data file
	ifstream mapFile;			// Data file
	ofstream newFile;			// File to save output data
	string line = "";			// text line
	string oldLine = "";		// line to be replaced
	string newLine = "";		// new line to replace oldLine

	cout << "Input file name: ";
	cin >> textFileName;
	cout << "Input map file: ";
	cin >> mapFileName;
	string newFileName = textFileName + ".rev";	// new file name to save output
	textFile.open(textFileName.c_str());
	newFile.open(newFileName.c_str());

	if (!textFile) {
		cout << "Can't open file" << endl;
		exit(1);
	}

	while (getline(textFile, line)) {
		mapFile.open(mapFileName.c_str());
		if (!mapFile) {
			cout << "Can't open file" << endl;
			exit(1);
		}
		while (getline(mapFile, oldLine, ':')) {
			getline(mapFile, newLine, '\n');
			replaceWord(line, oldLine, newLine);
		}
		mapFile.close();
		newFile << line;
	}
	newFile.close();
	textFile.close();

	return 0;
}

void replaceWord(string& txt, string map1, string map2) {
	string s = map2.substr(1, map2.length());		// string to cut " " from map2

	size_t n = 0;
	while ((n = txt.find(map1, n)) != -1) {
		txt.replace(txt.find(map1), map1.length(), s);
		n = n + s.length();
	}

	return;
}