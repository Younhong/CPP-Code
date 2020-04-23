/* written by 21400022 Younhong Ko
 * email: sjgkfkadk@hanmail.net
 * implementation date: 2016-11-30 
 * This program is to manage personal information through sorted email address.
 * There are five operations in this program which are load, delete, insert, update, save.
 * If any command beside those operations are entered, it will not execute any operations and end program.
 * This program is made and executed in g++ compiler Vim.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// struct to store multiple data at one node
struct NodeData {
	string dept;
	string name;
	string email;
	string birthyear;
	string birthmonth;
	string birthdate;
};
// struct to connect nodes
struct Node {
	NodeData data;
	Node* link;		// link to connect current node with next node
};
typedef Node* NodePtr;
// class type to compute operation
class NodeOperation {
	public:
		NodeOperation();
		void Load(ifstream& file);
		void Delete(string email);
		void Insert(NodeData data);
		void Update(NodeData data);
		void Save(ofstream& file);
		bool IsEmpty() const;
		~NodeOperation();
	private:
		NodePtr headPtr;	// first data from linked list
		NodePtr lastPtr;	// last data from linked list
};
// constructor function to allocate memory of list object
NodeOperation:: NodeOperation() {
	headPtr = NULL;
	lastPtr = headPtr;
}
// Loading operation: read text file and store five types of data on NodeData. After storing data, call insert function to put them on sorted dynamic linked list.
void NodeOperation:: Load(ifstream& file) {
	NodeData nd;	// variable to store data as struct as reading lines from text.

	while (getline(file, nd.dept, ';')) {
		getline(file, nd.name, ';');
		nd.name = nd.name.substr(1, nd.name.length());
		getline(file, nd.email, ';');
		nd.email = nd.email.substr(1, nd.email.length());
		getline(file, nd.birthyear, ';');
		nd.birthyear = nd.birthyear.substr(1, nd.birthyear.length());
		getline(file, nd.birthmonth, ';');
		nd.birthmonth = nd.birthmonth.substr(1, nd.birthmonth.length());
		getline(file, nd.birthdate, '\n');			
		nd.birthdate = nd.birthdate.substr(1, nd.birthdate.length());
		Insert(nd);
	}

	return;
}
// find email address in list that matches given email address and delete that node. If list is empty or email is not found, no operations will be done.
void NodeOperation:: Delete(string email) {
	NodePtr prevPtr = NULL;			// previous node
	NodePtr currPtr = headPtr;		// current node

	if (IsEmpty())
		cout << "No data to delete" << endl;
	while (currPtr != NULL && currPtr->data.email != email && currPtr->data.email < email) {
		prevPtr = currPtr;
		currPtr = currPtr->link;
	}
	if (currPtr != NULL && currPtr->data.email == email) {
		if (currPtr == headPtr)
			headPtr = currPtr->link;
		else
			prevPtr->link = currPtr->link;
		if (currPtr == lastPtr)
			lastPtr = prevPtr;
		delete currPtr;
	}	

	return;
}
// if email address already exist, then no insertion. If not, insert data.
void NodeOperation:: Insert(NodeData data) {
	NodePtr currPtr, prevPtr;
	NodePtr newPtr = new Node;		// new node to store data
	newPtr->data = data;

    if (IsEmpty()) {
        newPtr->link = NULL;
        headPtr = newPtr;
        lastPtr = newPtr;
    }
    else {
        currPtr = headPtr;
        prevPtr = NULL;
		while (currPtr != NULL && currPtr->data.email != data.email && currPtr->data.email < data.email) {
		    prevPtr = currPtr;
		    currPtr = currPtr->link;
		}
		if (currPtr != NULL && currPtr->data.email == data.email) {
			cout << "Email is already in the list" << endl;
			return;
		}
		newPtr->link = currPtr;
		if (prevPtr == NULL)
		    headPtr = newPtr;
		else
		    prevPtr->link = newPtr;
		if (currPtr == NULL)
		    lastPtr = newPtr;
    }

	return;
}
// if email address already exist, then change every element of data corresponding to that email. If not, insert data.
void NodeOperation:: Update(NodeData data) {
	NodePtr currPtr, prevPtr;
	NodePtr newPtr = new Node;
    newPtr->data = data;

    if (IsEmpty()) {
        newPtr = NULL;
        headPtr = newPtr;
        lastPtr = newPtr;
    }
    else {
        currPtr = headPtr;
        prevPtr = NULL;
		while (currPtr != NULL && currPtr->data.email != data.email && currPtr->data.email < data.email) {
		    prevPtr = currPtr;
		    currPtr = currPtr->link;
		}
		if (currPtr != NULL && currPtr->data.email == data.email) {
			currPtr->data = data;
			return;
		}
		newPtr->link = currPtr;
		if (prevPtr == NULL)
		    headPtr = newPtr;
		else
		    prevPtr->link = newPtr;
		if (currPtr == NULL)
		    lastPtr = newPtr;
    }

	return;
}
// save all informations in linked list to output file. If there are no data, then it won't be saved.
void NodeOperation:: Save(ofstream& file) {
	NodePtr currPtr = headPtr;

	if (IsEmpty())
		cout << "No data to save" << endl;

	while (currPtr != NULL) {
		file << currPtr->data.dept << "; ";
		file << currPtr->data.name << "; "; 
		file << currPtr->data.email << "; "; 
		file << currPtr->data.birthyear << "; "; 
		file << currPtr->data.birthmonth << "; "; 
		file << currPtr->data.birthdate << endl;
		currPtr = currPtr->link;
	}

	return;
}
// operation to check empty list
bool NodeOperation:: IsEmpty() const {
	return (headPtr == NULL);
}
// destructor function to deallocate memory of object
NodeOperation::~NodeOperation()
{
	NodePtr tempPtr;		// temporary node to delete node
	NodePtr currPtr = headPtr;
	while(currPtr != NULL)
	{
		tempPtr = currPtr;
		currPtr = currPtr->link;
		delete tempPtr;
	}
}

int main() {	
	NodeOperation no;			// object to use class function	
	ifstream inputTextFile;		// input data file
	ofstream outputTextFile;	// output data file
	string command;				// command to execute operation
	string textFileName;		// name of file to read or write data
	string dept, name, email, birthyear, birthmonth, birthdate;		// input data
	NodeData newdata;			// node for input data

	cout << "Enter functions you want to execute(enter quit to exit):" << endl;

	// it will not terminate until you put ' '
	while (getline(cin, command, ' ')) {
		if (command == "load") {
			getline(cin, textFileName);
			inputTextFile.open(textFileName.c_str());
			if (!inputTextFile) {
				cout << "Can't open file" << endl;
				exit(1);
			}
			no.Load(inputTextFile);
			inputTextFile.close();
		}
		else if (command == "delete") {
			getline(cin, email);
			newdata.email = email;
			no.Delete(newdata.email);
		}
		// it will not terminate until you put ';' five times.
		else if (command == "insert") {
			getline(cin, dept, ';');
			newdata.dept = dept;
			getline(cin, name, ';');
			newdata.name = name.substr(1, name.length());
			getline(cin, email, ';');
			newdata.email = email.substr(1, email.length());
			getline(cin, birthyear, ';');
			newdata.birthyear = birthyear.substr(1, birthyear.length());
			getline(cin, birthmonth, ';');
			newdata.birthmonth = birthmonth.substr(1, birthmonth.length());
			getline(cin, birthdate);			
			newdata.birthdate = birthdate.substr(1, birthdate.length());
			no.Insert(newdata);
		}
		// it will not terminate until you put ';' five times.
		else if (command == "update") {
			getline(cin, dept, ';');
			newdata.dept = dept;
			getline(cin, name, ';');
			newdata.name = name.substr(1, name.length());
			getline(cin, email, ';');
			newdata.email = email.substr(1, email.length());
			getline(cin, birthyear, ';');
			newdata.birthyear = birthyear.substr(1, birthyear.length());
			getline(cin, birthmonth, ';');
			newdata.birthmonth = birthmonth.substr(1, birthmonth.length());
			getline(cin, birthdate);			
			newdata.birthdate = birthdate.substr(1, birthdate.length());
			no.Update(newdata);
		}
		else if (command == "save") {
			getline(cin, textFileName);
			outputTextFile.open(textFileName.c_str());
			no.Save(outputTextFile);
			outputTextFile.close();
		}
		else {
			cout << "You are requesting invalid operation" << endl;
			break;
		}
		cout << "Enter functions you want to execute(enter quit to exit):" << endl;
	}

	return 0;
}
