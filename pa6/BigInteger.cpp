#include<iostream>
#include<string>
#include<stdexcept>
#include<ctype.h>
#include"BigInteger.h"
#include"List.h"

#define power 3
#define base 100
BigInteger::BigInteger(){
	signum = 0;
	//List L;
	//digits = List();
}

BigInteger::BigInteger(std::string s){
	//s.substr(0, p) gets numbers from index 0 - p, then delete beginning part of the string to read next
	//s.erase(0, p) deletes front p numbers from string
	//use s.substr(0, 1) to read frontmost character in order to check sign
	if(s.length() == 0){
		throw std::invalid_argument("BigInteger: string Constructor: empty string");
	}
	signum = 0;
	//digits = List();
	/*
	for(unsigned long i = 0; i < s.length(); i += 1){
		if(!(std::isdigit(s[i]))){
			throw std::invalid_argument("BigInteger: string Constructor: non-numeric string");
		}
	}
	*/
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
	for(unsigned long i = 0; i < s.length(); i += 1){
		if(!(std::isdigit(s[i]))){
			throw std::invalid_argument("BigInteger: string Constructor: non-numeric string");
		}
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
		//std::cout << "n = " << std::to_string(n) << std::endl;
		digits.insertBefore(n);
	}
}

/*
BigInteger::BigInteger(const BigInteger& N){
	signum = 0;
	//digits = List();
	
	//iterate through N and insert all List elements in N.digits into this
	List Ndigits = N.digits;
	List thisDigits = this->digits;
	Ndigits.moveFront();
	long A = Ndigits.peekNext();
	for(int P = 0; P < Ndigits.length(); P += 1){
		thisDigits.insertAfter(A);
		A = Ndigits.moveNext();
		//A = Ndigits.peekNext();
	}
}
*/
int BigInteger::sign() const{
	return signum;
}

int BigInteger::compare(const BigInteger& N) const{
	if(N.signum == -1 && this->signum == 1){
		std::cout << "first if" << std::endl;
		return 1;
	}
	if(this->signum == -1 && N.signum == 1){
		std::cout << "second if" << std::endl;
		return -1;
	}
	List Ndigits = N.digits;
	Ndigits.moveFront();
	List thisdigits = this->digits;
	thisdigits.moveFront();
	long B = Ndigits.peekNext();
	long A = thisdigits.peekNext();
	while(Ndigits.position()!= Ndigits.length()+1 || thisdigits.position() != thisdigits.length()+1){
		//std::cout << "Ndigits pos = " << Ndigits.position() << "Ndigits len = " << Ndigits.length() <<std::endl;
        	//std::cout << "this pos = " << thisdigits.position() << "this len = " << thisdigits.length() <<std::endl;

		//std::cout << "A = " << A << " B = " << B << std::endl;
		if(A < B){
		//	std::cout << "third if" << std::endl;
		//	std::cout << "A = " << A << "B = " << B << std::endl;
			return -1;
		}
		if(B < A){
			//std::cout << "fourth if" << std::endl;
			return 1;
		}
		B = Ndigits.moveNext();
		//B = N.digits.peekNext();
		A = thisdigits.moveNext();
		//A = Ndigits.peekNext();
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
	//long A = L.peekNext();
	while(L.position() != L.length()){
		long A = L.moveNext();
		long temp = (-1 * A);
		L.setBefore(temp);
		//L.moveNext();
		//A = L.peekNext();
	}
}

int normalizeList(List& L){
	if(L.front() < 0){
		negateList(L);
	}
	//long carry = 0;
	//long result = 0;
	L.moveBack();
	while(L.position() != 0){
		long A = L.movePrev();
		if(A >= base){
			//value is over base
			//long carry;
			//long result;
			long carry = A / base;
			long result = A % base;
			L.setAfter(result);
			if(L.position() == 0){
				L.insertBefore(carry);
				break;
			}
			else{
				L.setBefore(L.peekPrev() + carry);
			}
		}
		if(A < 0){
			//value is negative
			long carry = (A / base) -1;
			long result = (A % base) + base;
			L.setAfter(result);
			L.setBefore(L.peekPrev() + carry);
		}
	}
	if(L.front() < 0){
		return -1;
	}
	else{
		return 1;
	}
	//return 1;
	
}

std::string BigInteger::to_string(){
	
	std::string s = "";
	/*if(signum == 1){
		s += "+";
	}
	*/
	if(signum == -1){
		s += "-";
	}
	digits.moveFront();
	int fronttemp = 0;
	while(digits.position() != digits.length()){
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
std::ostream& operator<< (std::ostream& stream, BigInteger N){
	return stream << N.to_string();
}
/*
void somthing(BigInteger& N){
	std::cout << N.digits.to_string() << std::endl;
}
*/
int main(void){
	BigInteger A = BigInteger("+123456789417293471");
	BigInteger B = BigInteger("+123456789417293999");
	BigInteger C = BigInteger("+12345034001");
	std::cout << "A > B is = " << A.compare(B) << std::endl;
	std::cout << A.sign() << std::endl;
	std::cout << A << std::endl;
	B.negate();
	std::cout << B << std::endl;
	std::cout << C << std::endl;
	List L;
	L.insertBefore(21);
	L.insertBefore(-33);
	L.insertBefore(15);
	std::cout << L << std::endl;
	normalizeList(L);
	std::cout << L << std::endl;
	//somthing(A);
}
