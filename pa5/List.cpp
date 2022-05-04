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
	frontDummy = nullptr;
	backDummy = nullptr;
	beforeCursor = nullptr;
	afterCursor = nullptr;
	pos_cursor = -1;
	num_elements = 0;
}


