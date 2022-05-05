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
	pos_cursor = 0;
	num_elements = 0;
}

List::List(const List& L){
	frontDummy = new Node(-1);
	backDummy = new Node(-1);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
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

int List::length() const{
	return(num_elements);
}

ListElement List::front() const{
	if(num_elements <= 0){
		throw std::length_error("List: front(): empty List");
	}
	return (frontDummy->next->data);
}

ListElement List::back() const{
	if(num_elements <= 0){
		throw std::length_error("List: back(): empty List");
	}
	return (backDummy->prev->data);
}

int List::position() const{
	return(pos_cursor);
}

ListElement List::peekNext() const{
	if(pos_cursor >= num_elements){
		throw std::length_error("List: peekNext(): cursor at end of List");
	}
	return(afterCursor->data);
}

ListElement List::peekPrev() const{
	if(pos_cursor <= 0){
		throw std::length_error("List: peekPrev(): cursor at beginning of List");
	}
	return(beforeCursor->data);
}


