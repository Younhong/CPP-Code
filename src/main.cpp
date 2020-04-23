#include "file_array.h"

int main()
{
	string inputFileName1, inputFileName2;
	string command;

	cout << "command(trans ,add ,dot ,mul):" << endl;
	cin >> command;

	//**save inputfile 
	cout << "inputFile name:" << endl;
	cin >> inputFileName1;
	
	if (!command.compare("trans")) {
		file_array play(inputFileName1);
		play.makeArray(play.input1.file, play.data1);
		play.calculate(command);
		play.saveFile();
	}
	else
	{   //command-add,dot,mul need another inputfile
		cout << "inputFile name2:" << endl;
		cin >> inputFileName2;
		file_array play(inputFileName1, inputFileName2);
		play.makeArray(play.input1.file, play.data1);
		play.makeArray(play.input2.file, play.data2);
		play.calculate(command);
		play.saveFile();
		
	}
	return 0;
}