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
		inOrderString(s, R->left);
		s += R->key;
		s += " : ";
		s += R->val;
		s += " \n";
		inOrderString(s, R->right);
	}
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
		s += R->key;
		s += "\n";
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R != N){
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
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
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if(R == nil || k == R->key){
		return R;
	}
	else if(R->key > k){
		return search(R->left, k);
	}
	else{
		return search(R->right, k);
	}
}

//findMin()
Dictionary::Node* Dictionary::findMin(Node* R){
	if(R == nil){
		throw std::logic_error("Dictionary: findMin: nil Node");
	}
	while(R->left != nil){
		R = R->left;
	}
	return R;
}
//findMax()
Dictionary::Node* Dictionary::findMax(Node* R){
	if(R == nil){
		throw std::logic_error("Dictionary: findMax: nil Node");
	}
	while(R->right != nil){
		R = R->right;
	}
	return R;
}
//findNext()
Dictionary::Node* Dictionary::findNext(Node* N){
	if(N->right != nil){
		return(findMin(N->right));
	}
	Node* y = N->parent;
	while(y != nil && N == y->right){
		N = y;
		y = y->parent;
	}
	return y;
}
//findPrev()
Dictionary::Node* Dictionary::findPrev(Node* N){
	if(N->left != nil){
		return(findMax(N->left));
	}
	Node* y = N->parent;
	while(y != nil && N == y->left){
		N = y;
		y = y->parent;
	}
	return y;
}
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

valType& Dictionary::getValue(keyType k) const{
	//dont call contains(), takes too long to run
	Node* N = search(root, k);
	if(N == nil){	//does not contain
		throw std::logic_error("Dictionary: getValue(): does not contain key k");
	}
	return N->val;
	
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
	if(hasCurrent()){
		return current->val;
	}
	else{
		throw std::logic_error("Dictionary: currentVal(): current is nil");
	}
}

void Dictionary::clear(){
	 postOrderDelete(root);
}

void Dictionary::setValue(keyType k, valType v){
	Node* y = nil;
	Node* x = root;
	//Node* z = new Node(k, v);
	while(x != nil){
		y = x;
		if(k < x->key){
			x = x->left;
		}
		else if(k == x->key){
			x->val = v;
			return;
		}
		else{
			x = x->right;
		}
	}
	Node* z = new Node(k, v);
	z->parent = y;
	if(y == nil){
		root = N;
	}
	else if(N->key < y->key){
		y->left = N;
	}
	else{
		y->right = N;
	}
}

void Dictionary::Transplant(Node* u, Node* v){
	if(u->parent == 
}
void Dictionary::remove(keyType k){
	
}
