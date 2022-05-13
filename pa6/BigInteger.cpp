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
	if(sub == '-'){
		signum = -1;
		s.erase(0,1);
	}
	if(sub == '+'){
		signum = 1;
		s.erase(0,1);
	}
	char* end;
	long int n;
	digits.moveFront();
	while(s.length() > 0){
		std::string q = s.substr(0, 1);
		if(q.length() != 1){
			throw std::invalid_argument("Numerical string could not be parsed");
		}
		n = strtol(q, &end, 10);
		digits.insertBefore(n);
		s.erase(0,1);
	}
}

BigInteger::BigInteger(const BigInteger& N){
	signum = 0;
	digits = List L;
	
	//iterate through N and insert all List elements in N.digits into this
	N.digits.moveFront();
	ListElement A = N.digits.peekNext();
	for(int P = 0; P < N.digits.length(); P += 1){
		this->digits.insertBefore(A);
		N.digits.moveNext();
		A = N.digits.peekNext();
	}
}


