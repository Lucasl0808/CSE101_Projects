#include<iostream>
#include<string>
#include<stdexcept>
#include<ctype.h>
#include"BigInteger.h"
#include"List.h"

#define power 9
#define base 1000000000
BigInteger::BigInteger(){
	signum = 0;
	//List L;
	digits = List();
}

BigInteger::BigInteger(std::string s){
	//s.substr(0, p) gets numbers from index 0 - p, then delete beginning part of the string to read next
	//s.erase(0, p) deletes front p numbers from string
	//use s.substr(0, 1) to read frontmost character in order to check sign
	if(s.length() == 0){
		throw std::invalid_argument("BigInteger: string Constructor: empty string");
	}
	signum = 0;
	digits = List();
	for(unsigned long i = 0; i < s.length(); i += 1){
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
	//char* end;
	long int n;
	while(s.length() >= power){
		std::string q = s.substr(s.length()-power , power);	
		n = stol(q);
		digits.insertAfter(n);
		s.erase(s.length() - power ,power);
	}
	if(s.length() != 0){
		n = stol(s);
		digits.insertBefore(n);
	}
}

BigInteger::BigInteger(const BigInteger& N){
	signum = 0;
	digits = List();
	
	//iterate through N and insert all List elements in N.digits into this
	List Ndigits = N.digits;
	List thisDigits = this->digits;
	Ndigits.moveFront();
	long A = Ndigits.peekNext();
	for(int P = 0; P < Ndigits.length(); P += 1){
		thisDigits.insertBefore(A);
		Ndigits.moveNext();
		A = Ndigits.peekNext();
	}
}

int BigInteger::sign() const{
	return signum;
}

int BigInteger::compare(const BigInteger& N) const{
	List Ndigits = N.digits;
	Ndigits.moveFront();
	List thisdigits = this->digits;
	thisdigits.moveFront();
	long B = Ndigits.peekNext();
	long A = thisdigits.peekNext();
	while(Ndigits.position()!= Ndigits.length() || thisdigits.position() != thisdigits.length()){
		if(A < B){
			return 1;
		}
		if(B < A){
			return -1;
		}
		Ndigits.moveNext();
		B = N.digits.peekNext();
		thisdigits.moveNext();
		A = Ndigits.peekNext();
	}
	return 0;
}

void BigInteger::makeZero(){
	if(digits.length() == 0){
		return;
	}
	digits.moveFront();
	while(digits.position() != digits.length()){
		digits.eraseAfter();
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
		signum *= -1;
	}
}

//helper functions
//negateList reverses all the signs of the List given 
void negateList(List& L){
	L.moveFront();
	long A = L.peekNext();
	while(L.position() != L.length()){
		long temp = (-1 * A);
		L.setAfter(temp);
		L.moveNext();
		A = L.peekNext();
	}
}

int normalizeList(List& L){
	return 0;
}

std::string BigInteger::to_string const{
	std::string s = "";
	if(signum == 1){
		s += "+";
	}
	if(signum == -1){
		s += "-";
	}
	digits.moveFront();
	int fronttemp = 0;
	while(digits.position() != 0){
		if(fronttemp == 0){
			std::string temp = std::to_string(digits.moveNext());
			fronttemp += 1;
			s += temp;
		}
		else{
			std::string temp = std::to_string(digits.moveNext());
			unsigned long tlen = temp.length();
			while(tlen != power){
				s += "0";
				tlen += 1;
			}
			s += temp;
		}
	}
	return s;
}
std::ostream& operator<< (std::ostream& stream, const BigInteger& N){
	return stream << N.BigInteger::to_string();
}

int main(void){
	BigInteger A = BigInteger("+123456789");
	std::cout << A << endl;
}
