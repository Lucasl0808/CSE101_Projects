#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
	List L;
	cout << endl;
	L.insertAfter(2);
	L.insertAfter(1);
	cout << "List L = " << L << endl;
}
