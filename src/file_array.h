#include <fstream>
#include <string>
#include <iostream>

using namespace std;

typedef struct
{
	float **arr;
	int row;
	int col;
}ARRAY;

typedef struct
{
	string filename;
	ifstream file;
}INPUT_FILE;

typedef struct
{
	string filename;
	ofstream file;
}OUTPUT_FILE;

class file_array {
	public:
		ARRAY data1;
		ARRAY data2;
		ARRAY result;
		INPUT_FILE input1;
		INPUT_FILE input2;
		OUTPUT_FILE output;
		file_array(string );
		file_array(string, string);
		
		//***array function 
		void makeArray(ifstream & , ARRAY &);//** make array from input file information 
		void saveArray(ifstream & , ARRAY &);//**save information to array element
		void initializeArray(ARRAY & data);//** set initial condition to make array
										   
		//***command function
		void trans();
		void add();
		void dot();
		void mul();
		void calculate(string cmd);
		//***save newfile
		void saveFile(); 

};


