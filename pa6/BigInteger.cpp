#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

BigInteger::BigInteger(){
	signum = 0;
	digits = List L;
}

BigInteger::BigInteger(std::string s){
	//s.substr(0, p) gets numbers from index 0 - p, then delete beginning part of the string to read next
	//s.erase(0, p) deletes front p numbers from string
	//use s.substr(0, 1) to read frontmost character in order to check sign
	
	signum = 0;
	digits = List L;
	
	std::string sub = s.substr(0,1);
	if(sub == "-"){
		signum = -1;
		s.erase(0,1);
	}
	char* end;
	long int n;
	digits.moveFront();
	while(s.length() > 0){
		std::string q = s.substr(0, 2);
		n = strtol(q, &end, 100);
		digits.insertBefore(n);
		s.erase(0,2);
	}
}

BigInteger::BigInteger(const BigInteger& N){
	signum = 0;
	digits = List L;
	
	
}
