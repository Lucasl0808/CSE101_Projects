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
		s += std::to_string(R->val);
		s += "\n";
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
		//remove(R->key);
		delete R;
	}
}

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

Dictionary::Node* Dictionary::findMin(Node* R){
	if(R == nil){
		throw std::logic_error("Dictionary: findMin: nil Node");
	}
	while(R->left != nil){
		R = R->left;
	}
	return R;
}
Dictionary::Node* Dictionary::findMax(Node* R){
	if(R == nil){
		throw std::logic_error("Dictionary: findMax: nil Node");
	}
	while(R->right != nil){
		R = R->right;
	}
	return R;
}
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
	root = nil;
	current = nil;
	num_pairs = 0;
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
			//delete z;
			return;
		}
		else{
			x = x->right;
		}
	}
	Node* z = new Node(k, v);
	z->parent = y;
	z->left = nil;
	z->right = nil;
	if(y == nil){
		root = z;
	}
	else if(z->key < y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}
	num_pairs += 1;
}

void Dictionary::Transplant(Node* u, Node* v){
	if(u->parent == nil){
		root = v;
	}
	else if(u == u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	if(v != nil){
		v->parent = u->parent;
	}
}
void Dictionary::remove(keyType k){
	Node* z = search(root, k);
	if(z == nil){
		throw std::logic_error("Dictionary: remove(): tree does not contain key k");
	}
	if(z->left == nil){
		Transplant(z, z->right);
	}
	else if(z->right == nil){
		Transplant(z, z->left);
	}
	else{
		Node* y = findMin(z->right);
		if(y->parent != z){
			Transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		Transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	delete z;
	num_pairs -= 1;
}

void Dictionary::begin(){
	if(num_pairs == 0){
		return;
	}
	current = findMin(root);
}

void Dictionary::end(){
	if(num_pairs == 0){
		return;
	}
	current = findMax(root);
}

void Dictionary::next(){
	if(!(hasCurrent())){
		throw std::logic_error("Dictionary: next(): current iterator is not defined");
	}
	current = findNext(current);
}

void Dictionary::prev(){
	if(!(hasCurrent())){
		throw std::logic_error("Dictionary: prev(): current iterator is not defined");
	}
	current = findPrev(current);
	
}



std::string Dictionary::to_string() const{
	std::string s = "";
	Node* r = root;
	inOrderString(s, r);
	//s += "\n";
	//preOrderString(s, r);
	return s;
}

std::string Dictionary::pre_string() const{
	std::string s = "";
	Node* r = root;
	preOrderString(s, r);
	return s;
}

bool Dictionary::equals(const Dictionary& D) const{
	std::string first = this->to_string();
	std::string second = D.to_string();
	if(first == second){
		return true;
	}
	else{
		return false;
	}
}

std::ostream& operator<< (std::ostream& stream, Dictionary& D){
	return stream << D.Dictionary::to_string();
}

bool operator== (const Dictionary& A, const Dictionary& B){
	return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D){
	if(this != &D){
		Dictionary temp = D;
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this;
}


