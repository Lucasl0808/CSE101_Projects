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

void List::setAfter(ListElement x){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: setAfter(): cursor is at end of List");
	}
	afterCursor->data = x;
}

void List::setBefore(ListElement x){
	if(pos_cursor <= 0){
		throw std::range_error("List: setBefore(): cursor is at beginnging of List");
	}
	beforeCursor->data = x;
}

void List::eraseAfter(){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: eraseAfter(): cursor is at end of List");
	}
	if(num_elements == 1){
		frontDummy->next = backDummy;
		backDummy->prev = frontDummy;
		num_elements -= 1;
		afterCursor->prev = nullptr;
		afterCursor->next = nullptr;
		delete afterCursor;
		afterCursor = backDummy;
	}
	else{
		beforeCursor->next = afterCursor->next;
		afterCursor->next->prev = beforeCursor;
		afterCursor->next = nullptr;
		afterCursor->prev = nullptr;
		delete afterCursor;
		afterCursor = beforeCursor->next;
		num_elements -= 1;
	}
}

void List::eraseBefore(){
	if(pos_cursor <= 0){
		throw std::range_error("List: eraseBefore(): cursor is at the beginning of List");
	}
	if(num_elements == 1){
		frontDummy->next = backDummy;
		backDummy->prev = frontDummy;
		num_elements -=1;
		beforeCursor->next = nullptr;
		beforeCursor->prev = nullptr;
		delete beforeCursor;
		beforeCursor = frontDummy;
		pos_cursor -=1;
	}
	else{
		afterCursor->prev = beforeCursor->prev;
		beforeCursor->prev->next = afterCursor;
		beforeCursor->next = nullptr;
		beforeCursor->prev = nullptr;
		delete beforeCursor;
		num_elements -=1;
		pos_cursor -=1;
		beforeCursor = afterCursor->prev;
	}
}

int List::findNext(ListElement x){
	Node* N = nullptr;
	for(N = afterCursor; N != backDummy; N = N->next){
		if(N->data == x){
			moveNext();
			return beforeCursor->data;
		}
		moveNext();
	}
	return -1;
}

int List::findPrev(ListElement x){
	Node* N = nullptr;
	for(N = beforeCursor; N != frontDummy; N = N->prev){
		if(N->data == x){
			movePrev();
			return afterCursor->data;
		}
		movePrev();
	}
	return -1;
}

//cleanup here

List List::concat(const List& L) const{
	List G;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;
	while(N != this->backDummy){
		G.insertBefore(N->data);
		N = N->next;
	}
	while(M != L.backDummy){
		G.insertBefore(M->data);
		M = M->next;
	}
	return G;
}

std::string List::to_string() const{
	Node* N = nullptr;
	std::string s = "";
	
	for(N = frontDummy->next; N != backDummy; N = N->next){
		s += std::to_string(N->data)+" ";
	}
	return s;
}

std::ostream& operator<< (std::ostream& stream, const List& L){
	return stream << L.List::to_string();
}
