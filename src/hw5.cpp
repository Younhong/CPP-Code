/* written by 21400022 Younhong Ko
 * email: sjgkfkadk@hanmail.net
 * implementation date: 2016-11-14
 * This program can run 4 commands which are adding,multiplying, transposing, and dot multiplication which is same as HW#4. Unlike HW#4, this program uses class.
 * This program is made and compiled in g++ compiler Vim.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

const int SIZE = 50;

// class type to compute operation
class matrix_operation {
		int row, col, newRow, newCol, numberOfCol;
	public:
		void add(ifstream& file1, ifstream& file2, ofstream& file3, int row, int col);
		void mul(ifstream& file1, ifstream& file2, ofstream& file3, int row, int col);
		void trans(ifstream& file1, ofstream& file2, int col, int row);
		void dot(ifstream& file1, ifstream& file2, ofstream& file3, int newRow, int newCol, int numberOfCol);
};

int main() {
	matrix_operation mo;
	string text1 = "";				// name of file to read data
	string text2 = "";				// name of file to read second data
	string out = "";				// name of file to save
	ifstream textFile1;				// data file
	ifstream textFile2;				// data file2
	ofstream resultFile;			// saving file
	string command = "";			// command to execute
	int numberOfRow, numberOfCol;	// number of columns(first file)
	int row2, col2;					// number of columns(second file)

	cout << "Input first file name: ";
	cin >> text1;
	cout << "Input second file name: ";
	cin >> text2;
	cout << "Input command to execute: Enter add, mul, trans, or dot: ";
	cin >> command;
	cout << "Input output file name: ";
	cin >> out;

	textFile1.open(text1.c_str());
	textFile2.open(text2.c_str());
	resultFile.open(out.c_str());

	if (!textFile1 || !textFile2) {
		cout << "Can't open file" << endl;
		exit(1);
	}

	textFile1 >> numberOfRow;
	textFile1 >> numberOfCol;
	textFile2 >> row2;
	textFile2 >> col2;

	if (command == "add") {
		if (numberOfRow == row2 && numberOfCol == col2) {
			mo.add(textFile1, textFile2, resultFile, numberOfRow, numberOfCol);
		}
		else
			cout << "Cannot execute add command" << endl;
	}
	else if (command == "mul") {		
		if (numberOfRow == row2 && numberOfCol == col2) {
			mo.mul(textFile1, textFile2, resultFile, numberOfRow, numberOfCol);
		}
		else
			cout << "Cannot execute mul command" << endl;
	}
	else if (command == "trans") {
		mo.trans(textFile1, resultFile, numberOfCol, numberOfRow);
	}
	else if (command == "dot") {
		if (numberOfCol == row2) {
			mo.dot(textFile1, textFile2, resultFile, numberOfRow, col2, numberOfCol);
		}
		else
			cout << "Cannot execute dot command" << endl;
	}
	else
		cout << "Invalid command" << endl;

	resultFile.close();
	textFile1.close();
	textFile2.close();
		
	return 0;
}
// Read arrays of two data files which has same number of rows and columns and add values at same indexes.
void matrix_operation:: add(ifstream& file1, ifstream& file2, ofstream& file3, int row, int col) {
	float f,g;
	char a,b;
	float x[SIZE][SIZE];		// array to store result

	file3 << row << " " << col << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			file1 >> f;
			file2 >> g;
			if (j != col - 1) {
				file1 >> a;
				file2 >> b;
			}
			x[i][j] = f + g;
			file3 << x[i][j];
			if (j != col - 1)
				file3 << ", ";
			}
		file3 << "" << endl;
	}

	return;
}
// Read arrays of two data files which has same number of rows and columns and multiply values at same indexes.
void matrix_operation:: mul(ifstream& file1, ifstream& file2, ofstream& file3, int row, int col) {
	float f,g;
	char a,b;
	float x[SIZE][SIZE];
	
	file3 << row << " " << col << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			file1 >> f;
			file2 >> g;
			if (j != col - 1) {
				file1 >> a;
				file2 >> b;
			}
			x[i][j] = f * g;
			file3 << x[i][j];
			if (j != col - 1)
				file3 << ", ";
			}
		file3 << "" << endl;
	}

	return;
}
// Read arrays of single data file, and change row and column.
void matrix_operation:: trans(ifstream& file1, ofstream& file2, int col, int row) {
	float f;
	char a;
	int newRow = col;
	int newCol = row;
	float x[SIZE][SIZE];
	
	file2 << newRow << " " << newCol << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			file1 >> f;
			if (j != col - 1) {
				file1 >> a;
			}
			x[j][i] = f;
		}
	}
	for (int i = 0; i < newRow; i++) {
		for (int j = 0; j < newCol; j++) {
			file2 << x[i][j];
			if (j != newCol - 1)
				file2 << ", ";
		}
		file2 << "" << endl;
	}	

	return;
}
// Read arrays of two data files and multiply matrix when column of first file is same as second file's row.
void matrix_operation:: dot(ifstream& file1, ifstream& file2, ofstream& file3, int newRow, int newCol, int numberOfCol) {
	int i,j,k;
	float f,g;
	char a,b;
	float x[SIZE][SIZE];	// array to store data of first file
	float y[SIZE][SIZE];	// array to store data of second file
	float z[SIZE][SIZE];	// array to store result

	file3 << newRow << " " << newCol << endl;
	// initialize array z
	for (i = 0; i < newRow; i++) {
		for (j = 0; j < newCol; j++) {
			z[i][j] = 0.0;
		}
	}
	// store first file's data on array x
	for (i = 0; i < newRow; i++) {
		for (j = 0; j < numberOfCol; j++) {
			file1 >> f;
			if (j != numberOfCol - 1)
				file1 >> a;					
			x[i][j] = f;
		}
	}
	// store second file's data on array y
	for (i = 0; i < numberOfCol; i++) {
		for (j = 0; j < newCol; j++) {
			file2 >> g;
			if (j != newCol- 1)
				file2 >> b;
			y[i][j] = g;
		}
	}
	// compute array z
	for (i = 0; i < newRow; i++) {
		for (j = 0; j < newCol; j++) {
			for (k = 0; k < numberOfCol; k++) {
				z[i][j] += x[i][k] * y[k][j];
			}
		}
	}
	// print elements of array z
	for (i = 0; i < newRow; i++) {
		for (j = 0; j < newCol; j++) {
			file3 << z[i][j];
			if (j != newCol - 1)
				file3 << ", ";
		}
		file3 << "" << endl;
	}

	return;
}
