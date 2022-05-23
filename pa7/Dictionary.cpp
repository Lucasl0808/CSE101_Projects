/* Lucas Lee
 * luclee
 * pa7
 * CSE101-02 Spring 2022
 */

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

Dictionary::Dictionary(){
	nil = new Node("*", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("*", -1);
	root = nil;
	current = nil;
	num_pairs = 0;

	this->root = D.root;
	this->current = D.current;
	this->num_pairs = D.num_pairs;
	//preorder copy to copy D's tree into this->tree, pass in D.nil to N parameter of preOrderCopy
	this->preOrderCopy(D.root, D.nil);
	
}

Dictionary::~Dictionary(){
	clear();
	delete nil;
}

void Dictionary::inOrderString(std::string& s, Node *R) const{
	if(R != nil){
		inOrderString(R->left);
		s += R->key;
		s += " : ";
		s += R->val;
		s += " \n";
		inOrderString(R->right);
	}
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
		s += R->key;
		s += "\n";
		preOrderString(R->left);
		preOrderString(R->right);
	}
}

void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R != N){
		setValue(R->key, R->val);
		preOrderCopy(R->left);
		preOrderCopy(R->right);
	}
}

void Dictionary::postOrderDelete(Node* R){
	if(R != nil){
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		remove(R->key);
	}
}

//search()


//findMin()

//findMax()

//findNext()

//findPrev()

int Dictionary::size() const{
	return num_pairs;
}

bool Dictionary::contains(keyType k) const{
	if(search(root, k) == nil){
		return false;
	}
	else{
		return true;
	}
}

valType& getValue(keyType k) const{
	//dont call contains(), takes too long to run
	
}

bool Dictionary::hasCurrent() const{
	if(current == nil){
		return false;
	}
	else{
		return true;
	}
}

keyType Dictionary::currentKey() const{
	if(hasCurrent()){
		return current->key;
	}
	else{
		throw std::logic_error("Dictionary: currentKey(): current is nil");
	}
}

valType& Dictionary::currentVal() const{
	//find out how to return address
	if(hasCurrent()){
		return current->val;
	}
	else{
		throw std::logic_error("Dictionary: currentVal(): current is nil");
	}
}
