#include<iostream>
#include<string>
#include<stdexcept>
#include<ctype.h>
#include"List.h"

#define power 9
#define base 1000000000
BigInteger::BigInteger(){
	signum = 0;
	digits = List L;
}

BigInteger::BigInteger(std::string s){
	//s.substr(0, p) gets numbers from index 0 - p, then delete beginning part of the string to read next
	//s.erase(0, p) deletes front p numbers from string
	//use s.substr(0, 1) to read frontmost character in order to check sign
	if(s.length() == 0){
		throw std::invalid_argument("BigInteger: string Constructor: empty string");
	}
	signum = 0;
	digits = List L;
	for(int i = 0; i < s.length(); i += 1){
		if(!(std::isdigit(s[i]))){
			throw std::invalid_argument("BigInteger: string Constructor: non-numeric string");
		}
	}
	//std::string sub = s.substr(0,1);
	if(s[0] == '-'){
		signum = -1;
		s.erase(0,1);
	}
	if(s[0] == '+'){
		signum = 1;
		s.erase(0,1);
	}
	while(s[0] == '0'){
		s.erase(0,1);
	}
	char* end;
	long n;
	while(s.length() >= power){
		std::string q = s.substr(0, power);
		
		n = strtol(q, &end, base);
		digits.insertBefore(n);
		s.erase(0,power);
	}
	if(s.length() != 0){
		n = strtol(s, &end, base);
		digits.insertBefore(n);
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

void BigInteger::negate(){
	digits.moveFront();
	long A = digits.peekNext();
	if(A == 0){
		return;
	}
	if(signum == 0){
		signum = -1;
	}
	else{
		signum *= -1
	}
}

//helper functions
//negateList reverses all the signs of the List given 
void negateList(List& L){
	L.moveFront();
	long A = L.peekNext();
	while(A != L.backDummy){
		long temp = (-1 * A);
		L.setAfter(temp);
		L.moveNext();
		A = L.peekNext();
	}
}


