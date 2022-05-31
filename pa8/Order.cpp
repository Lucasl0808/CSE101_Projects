/* Lucas Lee
 * luclee
 * pa7
 * CSE101-02 Spring 2022
 */

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
#include<fstream>

using namespace std;

int main(int argc, char *argv[]){
	ifstream in;
	ofstream out;
	if(argc != 3){
		cerr << "Usage: ./Order <input file> <output file>" << endl;
		exit(EXIT_FAILURE);
	}
	in.open(argv[1]);
	if(!in.is_open()){
		cerr << "Unable to open file " << argv[1] <<" for reading" << endl;
		exit(EXIT_FAILURE);
	}
	out.open(argv[2]);
	if(!out.is_open()){
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		exit(EXIT_FAILURE);
	}
	string line;
	int counter = 1;
	Dictionary D;
	while(getline(in, line)){
		D.setValue(line, counter);
		counter += 1;
	}
	
	out << D << endl << D.pre_string();
	//out << "\n" << endl;
	//string b = "";
	//D.preOrderString(b, D.root);
	//out << b << endl;
}
