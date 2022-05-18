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


BigInteger::BigInteger(const BigInteger& N){
	signum = N.sign();
	//digits = List();
	//iterate through N and insert all List elements in N.digits into this
	List Ndigits = N.digits;
	this->digits = Ndigits;
	/*
	Ndigits.moveFront();
	//long A = Ndigits.peekNext();
	for(int P = 0; P < Ndigits.length(); P += 1){
		long A = Ndigits.moveNext();
		std::cout << A << std::endl;
		thisDigits.insertBefore(A);
		//A = Ndigits.moveNext();
		//A = Ndigits.peekNext();
	}
	*/
}

int BigInteger::sign() const{
	return signum;
}

int BigInteger::compare(const BigInteger& N) const{
	if(N.signum == -1 && this->signum == 1){
		return 1;
	}
	if(this->signum == -1 && N.signum == 1){
		return -1;
	}
	List Ndigits = N.digits;
	Ndigits.moveFront();
	List thisdigits = this->digits;
	thisdigits.moveFront();
	//long B = Ndigits.peekNext();
	//long A = thisdigits.peekNext();
	while(Ndigits.position()!= Ndigits.length() || thisdigits.position() != thisdigits.length()){
		//std::cout << "Ndigits pos = " << Ndigits.position() << "Ndigits len = " << Ndigits.length() <<std::endl;
        	//std::cout << "this pos = " << thisdigits.position() << "this len = " << thisdigits.length() <<std::endl;
		long B = Ndigits.moveNext();
		long A = thisdigits.moveNext();
		//std::cout << "A = " << A << " B = " << B << std::endl;
		if(A < B){
			return -1;
		}
		if(B < A){
			return 1;
		}
		//B = Ndigits.moveNext();
		//B = N.digits.peekNext();
		//A = thisdigits.moveNext();
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
	int sign = 1;
	L.moveFront();
	while(L.front() == 0){
		L.eraseAfter();
	}
	if(L.front() < 0){
		negateList(L);
		sign = -1;
		
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
				//L.setAfter(result);
				L.setBefore(L.peekPrev() + carry);
			}
		}
		if(A < 0){
			//value is negative
			long carry = (A / base) -1;
			long result = (A % base) + base;
			L.setAfter(result);
			L.setBefore(L.peekPrev() + carry);
			if(A == 0 && L.position() == 1){
				L.eraseBefore();
				break;
			}
		}
	}
	if(sign == -1){
		return -1;
	}
	else{
		return 1;
	}
	//return 1;
	
}

void sumList(List& S, List A, List B, int sgn){
	//S = A + sgn* B
	S.clear();
	A.moveBack();
	B.moveBack();
	while(A.position() > 0 || B.position() > 0){
		if(A.position() == 0){
			long val = B.movePrev() * sgn;
			S.insertAfter(val);
			//B.movePrev();
			continue;
		}
		if(B.position() == 0){
			long val = A.movePrev();
			S.insertAfter(val);
			//A.movePrev();
			continue;
		}
		long sum = A.movePrev() + (B.movePrev() * sgn);
		S.insertAfter(sum);
		//A.movePrev();
		//B.movePrev();
	}
	//normalizeList(S);
}

void shiftList(List& L, int p){
	L.moveBack();
	for(int i = 0; i < p; i += 1){
		L.insertBefore(0);
	}
}

void scalarMultList(List& L, ListElement m){
	L.moveBack();
	while(L.position() > 0){
		long mult = L.movePrev() * m;
		//long mult = L.peekPrev() * m;
		L.setAfter(mult);
		//L.movePrev();
	}
}

BigInteger BigInteger::add(const BigInteger& N) const{
	//return new Biginteger = sum of this and N
	BigInteger R;
	sumList(R.digits, this->digits, N.digits, 1);
//	std::cout << R.digits << std::endl;
	R.signum = normalizeList(R.digits);
	return R;
}

BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger R;
	sumList(R.digits, this->digits, N.digits, -1);
	//std::cout << "digits= " << R.digits << std::endl;
	R.signum = normalizeList(R.digits);
	return R;
}

BigInteger BigInteger::mult(const BigInteger& N) const{
	BigInteger R;
	List Nd = N.digits;
	List copyN = N.digits;
	List m = this->digits;
	m.moveBack();
	int iteration = 0;
	while(m.position() > 0){
		//shiftList(copyN, iteration);
		copyN = Nd;
		long number = m.movePrev();
		scalarMultList(copyN, number);
		std::cout <<"temp sm = " << copyN << std::endl;
		shiftList(copyN, iteration);
                std::cout <<"temp sl = " << copyN << std::endl;
		List tempR = R.digits;
		sumList(R.digits, copyN, tempR, 1);
                std::cout <<"temp sum = " << copyN << std::endl;
		normalizeList(R.digits);
                std::cout <<"temp norm= " << copyN << std::endl;
		iteration += 1;
		
	}
	return R;
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

bool operator==(const BigInteger& A, const BigInteger &B){
	if(A.compare(B) == 0){
		return true;
	}
	else{
		return false;
	}
}
/*
void somthing(BigInteger& N){
	std::cout << N.digits.to_string() << std::endl;
}
*/
int main(void){
	BigInteger A = BigInteger("+35579758422123123");
	BigInteger B = BigInteger("+35579758433456456");
	BigInteger C = BigInteger("+12345034001");
	std::cout << "A < B is  " << A.compare(B) << std::endl;
	std::cout << B.sign() << std::endl;
	std::cout << A << std::endl;
	//B.negate();
	std::cout << B << std::endl;
	std::cout << C << std::endl;
	List L;
	List S;
	List P;
	L.insertBefore(35);
	L.insertBefore(57);
	L.insertBefore(97);
	S.insertBefore(14);
	S.insertBefore(90);
	S.insertBefore(82);
	std::cout << L << std::endl;
	//normalizeList(L);
	std::cout << S << std::endl;
	sumList(P, L, S, 1);
	std::cout << P << std::endl;
	BigInteger Q = A.add(B);
	std::cout << Q << std::endl;
	BigInteger M = A.sub(B);
	std::cout << "here " << M << std::endl;
	//shiftList(L, 3);
	//std::cout << L << std::endl;
	
	scalarMultList(L, 11);
	std::cout << "here " << L << std::endl;
	normalizeList(L);
	std::cout << L << std::endl;
	BigInteger N = BigInteger("123");
	BigInteger D = BigInteger("456");
	BigInteger G = N.mult(D);
	std::cout << G << std::endl;

	BigInteger T("+999");
	BigInteger TT("+999");
	std::cout << T << std::endl;
	List PO;
	PO.insertBefore(81);
	PO.insertBefore(81);
	PO.insertBefore(81);
	normalizeList(PO);
	std::cout << PO << std::endl;
	BigInteger TTT = T.mult(TT);
	std::cout << TTT << std::endl;
	BigInteger LL = A.mult(B);
	std::cout << LL << std::endl;
	//somthing(A);
	
}
