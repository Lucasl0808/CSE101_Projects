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
	cout << L.equals(M) << endl;
}
