/* Lucas Lee
 * luclee
 * pa5
 * CSE101-02 Spring 2022
 */

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D){
	List L;
	List R;
	D.moveFront();
	for(int i = 1; i <= D.length(); i += 1){
		D.moveNext();
		if(D.length() % 2 == 0){
			if(i <= D.length()/2){
				L.insertBefore(D.peekPrev());
			}
			else{
				R.insertBefore(D.peekPrev());
			}
		}
		else{
			if(i <= (D.length() -1) /2){
				L.insertBefore(D.peekPrev());
			}
			else{
				R.insertBefore(D.peekPrev());
			}
		}
	}
	R.moveFront();
	L.moveFront();
	D.clear();
	int total_length = L.length() + R.length();
	for(int j = 1; j <= total_length; j += 1){
		if(j % 2 == 1){
			D.insertBefore(R.peekNext());
			R.moveNext();
		}
		else{
			D.insertBefore(L.peekNext());
			L.moveNext();
		}
	}
}

int main(int argc, char *argv[]){
	if(argc != 2){
		cout << "Usage: ./Shuffle <int>" << endl;
		exit(1);
	}
	int cards = atoi(argv[1]);
	cout << "deck size	 shuffle count" << endl;
	cout << "------------------------------" << endl;
	List L;
	List C;
	for(int i = 1; i <= cards; i += 1){
		L.insertBefore(i);
		C.insertBefore(i);
		int count = 1;
		shuffle(L);
		while(!(L == C)){
			shuffle(L);
			count += 1;
		}
		cout << " " << i;
		cout << "		" << count << endl;

	}
	return 1;
}
