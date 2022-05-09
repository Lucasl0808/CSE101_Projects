#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
	List L;
	//cout << endl;
	L.insertAfter(2);
	L.insertAfter(1);
	L.moveNext();
	L.moveNext();
	L.insertAfter(4);
	L.insertBefore(3);
	L.insertAfter(4);
	cout << "List L = " << L << endl;
	cout << L.position() <<endl;
	L.moveFront();
	L.findNext(4);
	cout << L.position() << endl;
	L.moveBack();
	L.findPrev(1);
	cout << L.position() << endl;
	List Y;
	Y.insertBefore(1);
	Y.insertBefore(1);
	Y.insertBefore(1);
	List P = L.concat(Y);
	List M;
	M.insertBefore(1);
	M.insertBefore(2);
	M.insertBefore(3);
	M.insertBefore(4);
	M.insertBefore(4);
	cout << "List M = " << M << endl;
	cout << "List P = " << P << endl;
	cout << "L == M " << (L==M?"true":"false") << endl;
	List G = L;
	cout << "List G = " << G << endl;
	List F;
	F.insertBefore(1);
	F.insertBefore(2);
	F.insertBefore(3);
	F.insertBefore(4);
	F.insertBefore(1);
	F.insertBefore(2);
	F.insertBefore(3);
	F.insertBefore(4);
	F.moveFront();
	F.moveNext();
	F.moveNext();
	F.moveNext();
	F.moveNext();
	F.moveNext();
	F.cleanup();
	cout << "List F = " << F << endl;
	cout << F.position() << endl;
	F.moveBack();
	F.movePrev();
	F.eraseAfter();
	cout << "List F = " << F << endl;
	List A;
	A.insertBefore(34);
	A.insertBefore(77);
	A.insertBefore(77);
	A.insertBefore(1);
	A.insertBefore(34);
	A.insertBefore(1);
	A.insertBefore(55);
	A.insertBefore(77);
	cout << "List A = " << A << endl;
	cout << A.position() << endl;
	A.moveBack();
	A.cleanup();
	cout << "List A = " << A << endl;
	cout << A.position() << endl;
	cout << A.peekPrev() << endl;
	cout << A.findPrev(1) << endl;
}
