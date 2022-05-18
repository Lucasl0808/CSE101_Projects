/* Lucas Lee
 * luclee
 * pa6
 * CSE101-02 Spring 2022
 */
#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"

using namespace std;

int main(int argc, char *argv[]){
	ifstream in;
	ofstream out;
	if(argc != 3){
		cerr << "Usage: ./Arithmetic <input file> <output file>" << endl;
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
	string num1, empty, num2;
	getline(in, num1);
	getline(in, empty);
	getline(in, num2);
	
	BigInteger A(num1);
	BigInteger B(num2);
	
	out << A << endl << endl;
	out << B << endl << endl;
	
	BigInteger ad = A + B;
	
	out << ad << endl << endl;

	BigInteger su = A - B;
	
	out << su << endl << endl;

	BigInteger zero = A - A;
	
	out << zero << endl << endl;

	BigInteger temp1(num1);
	BigInteger temp2(num2);
	
	temp1 += A;
	temp1 += A;
	//temp1 = 3A
	
	temp2 += B;
	//temp2 = 2B
	
	BigInteger Z = temp1 - temp2;

	out << Z << endl << endl;

	BigInteger AB = A * B;
	
	out << AB << endl << endl;

	BigInteger AA = A * A;

	out << AA << endl << endl;

	BigInteger BB = B * B;
	
	out << BB << endl << endl;

	BigInteger temp3(num1);
	BigInteger temp4(num2);
	
	for(int p = 0; p < 8; p += 1){
		temp3 += A;
	}
	for(int o = 0; o < 3; o += 1){
		temp3 *= A;
	}

	for(int x = 0; x < 15; x += 1){
		temp4 += B;
	}
	for(int y = 0; y < 4; y += 1){
		temp4 *= B;
	}

	BigInteger large = temp3 + temp4;

	out << large << endl;
}
