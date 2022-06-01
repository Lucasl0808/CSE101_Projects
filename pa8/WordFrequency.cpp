#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
#include<fstream>

using namespace std;
int main(int argc, char *argv[]){
	ifstream in;
	ofstream out;
	//int line_count;
	size_t begin, end, len;
	string token;
	string tokenBuffer;
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
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
	int counter = 0;
	Dictionary D;
	while(getline(in, line)){
		counter +=1;
		len = line.length();
		tokenBuffer = "";
		begin = min(line.find_first_not_of(delim, 0), len);
		end = min(line.find_first_of(delim, begin), len);
		token = line.substr(begin, end-begin);
		//for(int i = 0; i < token.length(); i ++){
		//	token[i] = tolower(token[i]);
		//}
		while(token != ""){
			for(string::size_type i = 0; i < token.length(); i ++){
				token[i] = tolower(token[i]);
			}
			if(D.contains(token)){
				D.getValue(token) += 1;
			}
			else{
				D.setValue(token, 1);
			}
			tokenBuffer += "   "+ token + "\n";
			begin = min(line.find_first_not_of(delim, end+1), len);
			end = min(line.find_first_of(delim, begin), len);
			token = line.substr(begin, end-begin);
		}
	}
	out << D << endl;
	in.close();
	out.close();
	return(EXIT_SUCCESS);
}
