
#include "file_array.h"

using namespace std;

file_array::file_array(string filename)
{//**constructor for trans
	input1.filename = filename;
	input1.file.open(filename);
	cout << "ouput file name:";
	cin >> output.filename;
	output.file.open(output.filename);
}

file_array::file_array(string filename1, string filename2)
{//**constructor for add,mul, dot
	input1.filename = filename1;
	input1.file.open(filename1);
	input2.filename = filename2;
	input2.file.open(filename2);
	cout << "ouput file name:";
	cin >> output.filename;
	output.file.open(output.filename);

}

void file_array::makeArray(ifstream & inputFile, ARRAY & data)
{  //** make array from input file information 

	string str;
	int num;
	int	count = 0; // num: string number to float number 

				   //**find row and col
	while (count < 2)
	{
		inputFile >> str;
		if (str != " ")
		{
			num = stoi(str);
			if (count == 0) data.row = num;
			else data.col = num;
			count++;
		}
	}

	//**make array
	initializeArray(data);

	//**save array each element 
	saveArray(inputFile, data);
}

void file_array::initializeArray(ARRAY & data)
{//** set initial condition to make array
	data.arr = (float **)malloc(sizeof(float *)*(data.row));
	for (int i = 0; i < data.row; i++)
	{
		data.arr[i] = (float *)malloc(sizeof(float)*(data.col));
	}

	for (int i = 0; i < data.row; i++)
		for (int j = 0; j < data.col; j++)
			data.arr[i][j] = 0.0;
}

void file_array::saveArray(ifstream &file, ARRAY &data)
{//**save information to array 
	string str;
	float temp[100];
	int i = 0;
	//**process string to float 
	while (file >> str)
	{

		if (str != " ") {
			temp[i++] = stof(str);
		}
	}

	//**save each element
	int k = 0; // 
	for (int i = 0; i < data.row; i++)
		for (int j = 0; j < data.col; j++)
			data.arr[i][j] = temp[k++];
}

void file_array::trans()
{ //**trans for one file 
	result.row = data1.col;
	result.col = data1.row;
	initializeArray(result);
	for (int i = 0; i < result.row; i++)
		for (int j = 0; j < result.col; j++)
			result.arr[i][j] = data1.arr[j][i];
}

void file_array::add()
{
	if ((data1.row == data2.row) && (data1.col == data2.col)) //precondition
	{
		result.row = data1.row;
		result.col = data1.col;
		initializeArray(result);
		for (int i = 0; i < result.row; i++)
			for (int j = 0; j < result.col; j++)
				result.arr[i][j] = data1.arr[i][j] + data2.arr[i][j];
	}
	else cout << "please check matrix size" << endl;
}

void file_array::dot()
{
	if (data1.col == data2.row)//precondiontion
	{
		result.row = data1.row;
		result.col = data2.col;
		initializeArray(result);
		for (int i = 0; i < result.row; i++)
			for (int j = 0; j < result.col; j++)
				for (int k = 0; k < data1.col; k++)
					result.arr[i][j] += data1.arr[i][k] * data2.arr[k][j];
	}
	else  cout << "please check matrix size" << endl;
}

void file_array::mul()
{
	if ((data1.row == data2.row) && (data1.col == data2.col)) //precondition
	{
		result.row = data1.row;
		result.col = data1.col;
		initializeArray(result);
		for (int i = 0; i < result.row; i++)
			for (int j = 0; j < result.col; j++)
				result.arr[i][j] = data1.arr[i][j] * data2.arr[i][j];
	}
	else cout << "please check matrix size" << endl;
}

void file_array::saveFile()
{//**save result in new file
	string row, col;
	row = to_string(result.row);
	col = to_string(result.col); // convert for saving file
	output.file << row + " ";
	output.file << col + "\n";

	for (int i = 0; i < result.row; i++)
	{
		for (int j = 0; j < result.col; j++)
		{
			output.file << result.arr[i][j];
			if (j<result.col - 1) output.file << ", ";
		}
		output.file << "\n";
	}
}

void file_array::calculate(string cmd)
{
	if (!cmd.compare("trans")) trans();
	else if (!cmd.compare("add")) add();
	else if (!cmd.compare("dot")) dot();
	else if (!cmd.compare("mul")) mul();
}
