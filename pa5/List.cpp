#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

List::Node:Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

List::List(){
	frontDummy = new Node(-1);
	backDummy = new Node(-1);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = -1;
	num_elements = 0;
}

List::List(const List& L){
	frontDummy = new Node(-1);
	backDummy = new Node(-1);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = -1;
	num_elements = 0;
	
	Node* N = L.front;
	while(N != nullptr){
		this->insertBefore(N->data);
		N = N->next;
	}
}

List::~List(){
	clear();
	delete frontDummy;
	delete backDummy;
}
