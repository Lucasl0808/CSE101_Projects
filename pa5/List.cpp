#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

List::Node::Node(ListElement x){
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
	
	Node* N = frontDummy->next;
	while(N != backDummy){
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
		throw std::range_error("List: peekNext(): cursor at end of List");
	}
	return(afterCursor->data);
}

ListElement List::peekPrev() const{
	if(pos_cursor <= 0){
		throw std::range_error("List: peekPrev(): cursor at beginning of List");
	}
	return(beforeCursor->data);
}

void List::clear(){
	if(num_elements == 0){
		return;
	}
	moveFront();
	while(frontDummy->next != backDummy){
		eraseAfter();
	}
}

void List::moveFront(){
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
}

void List::moveBack(){
	pos_cursor = num_elements;
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

ListElement List::moveNext(){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: moveNext(): cursor is at end of List");
	}
	pos_cursor += 1;
	beforeCursor = afterCursor;
	afterCursor = afterCursor->next;
	return(beforeCursor->data);
}

ListElement List::movePrev(){
	if(pos_cursor <= 0){
		throw std::range_error("List: movePrev(): cursor is at beginning of List");
	}
	pos_cursor -= 1;
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor->prev;
	return(afterCursor->data);
}

void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	if(num_elements == 0){
		frontDummy->next = N;
		backDummy->prev = N;
		N->prev = frontDummy;
		N->next = backDummy;
		afterCursor = N;
		num_elements += 1;
		return;
	}
	else{
		beforeCursor->next = N;
		afterCursor->prev = N;
		N->prev = beforeCursor;
		N->next = afterCursor;
		afterCursor = N;
		num_elements += 1;
		return;
	}
}

void List::insertBefore(ListElement x){
	Node *N = new Node(x);
	if(num_elements == 0){
		frontDummy->next = N;
		backDummy->prev = N;
		N->prev = frontDummy;
		N->next = backDummy;
		beforeCursor = N;
		num_elements += 1;
		return;
	}
	else{
		beforeCursor->next = N;
		afterCursor->prev = N;
		N->prev = beforeCursor;
		N->next = afterCursor;
		beforeCursor = N;
		num_elements += 1;
		return;
	}
}
