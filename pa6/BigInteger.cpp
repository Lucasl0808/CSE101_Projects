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
	long A = N.digits.peekNext();
	for(int P = 0; P < N.digits.length(); P += 1){
		this->digits.insertBefore(A);
		N.digits.moveNext();
		A = N.digits.peekNext();
	}
}

int BigInteger::sign() const{
	return signum;
}

int BigInteger::compare(const BigInteger& N) const{
	N.digits.moveFront();
	this->digits.moveFront();
	long B = N.digits.peekNext();
	long A = this->digits.peekNext();
	while(A != N.digits.backDummy || B != this->digits.backDummy){
		if(A < B){
			return 1;
		}
		if(B < A){
			return -1;
		}
		N.digits.moveNext();
		B = N.digits.peekNext();
		this->digits.moveNext();
		A = N.digits.peekNext();
	}
	return 0;
}

void BigInteger::makeZero(){
	if(digits.length() == 0){
		return;
	}
	digits.moveFront();
	long A = digits.peekNext();
	while(A != digits.backDummy){
		digits.eraseAfter();
		A = digits.peekNext();
	}
}


