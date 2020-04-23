/* Sample code for HW#3 (ECE20018, Fall 2016)
 * This code replaces an input file with a map file,
 * and saves the revised one as an output file.
 * The input and the map files are user inputs. 
 * 
 * Oct. 13, 2016 
 * by hchoi@handong.edu
 */ 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void line_replace(string& line, string map_line);

int main() 
{
    string input_file, map_file; // file names
    string line, map_line; // lines from the files
    ifstream i_file, m_file; // input/map file streams
    ofstream o_file; // output file stream

    cout << "put input file and map file" << endl;
    cin >> input_file;
    cin >> map_file;

    i_file.open(input_file); // open the input file
    if (i_file){
        o_file.open(input_file+".rev");
    }else{
        cout << "no input file" << endl;
        return 0;
    }

    while(getline(i_file, line)){ 
        m_file.open(map_file);
        while(getline(m_file, map_line)){
            line_replace(line, map_line);
        }
        m_file.close();
        o_file << line << endl;
    }
}

// This function revises a given line with a map line
// The map line should be in the form of "source: target"
void line_replace(string& line, string map_line)
{
    string new_line;
    string src_str, trg_str;
    int idx;

    // separate source and target strings
    idx = map_line.find(": "); 
    src_str = map_line.substr(0, idx);
    trg_str = map_line.substr(idx+2, map_line.length());

    // replace the source str with the target str in the line
    idx = 0;
    while(true) {
        // if there is source string in the line
        if(line.substr(idx, src_str.length()) == src_str){
            new_line += trg_str;
            idx += src_str.length();
        }
        else{ // o.w., copy just one character 
            new_line += line.at(idx++); //new_line += line[idx++];
        }
        if(idx >= line.length()) break; // the end of the line
    }
    line = new_line;
}
