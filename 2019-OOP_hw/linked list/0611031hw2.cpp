#include "Link_List.h"

template <typename T>
Link_List<T>::Link_List(){  //constructor
	head = NULL;
	tail = NULL;
	size = 0;
}

template <typename T>
Link_List<T>::~Link_List(){  //distructor
	for(int i = 0; i < size; i++){
		delete_node();
	}
	head = NULL;
	tail = NULL;
}

template <typename T>
Link_List<T>::Link_List(const Link_List &right){  // copy constructor
	head = NULL; //constructor link list 2
	tail = NULL;
	size = 0;
	for(int i = 0; i < right.getsize(); i++){
		insert_node();
	} 
}

template <typename T>
int Link_List<T>::getSize() const{  //get size
	return size;
}

template <typename T>
const Link_List<T> &Link_List<T>::operator=(const Link_List &right){  // assignment operator
	this -> head = right -> head;
	this -> tail = right -> head;
	size = right.getsize();
}

template <typename T>
bool Link_List<T>::operator==(const Link_List &right) const{// equality operator
	if( this -> getsize() != right.getsize()){
		return false;
	}
	for(int i = 0; i < right.getsize(); i++){
		if(this -> value != right-> value){
			return false;
		}
	}
	return true;
}

template <typename T> 
T &Link_List<T>::operator[](int index){  //operator[]
	Int_Node<T>* current = new Int_Node<T>;
	current = head;
	for(int i = 0; i < index; i++){
		current = current -> next;
	}
	return current -> value;
}

template <typename T> 
T Link_List<T>::operator[](int index) const{  // subscript operator for const objects
	Int_Node<T>* current = new Int_Node<T>;
	current = head;
	for(int i = 0; i < index; i++){
		current = current -> next;
	}
	return current -> value;
}

template <typename T> 
bool Link_List<T>::insert_node(T value){	// insert an integer at the back of link list
	if(head == NULL){ // insert_node  at first head
		head = new Int_Node<T>;
		head -> next = NULL;
		head -> pre = NULL;
		head -> value = value;
		tail = head;
		size++;
	}
	else{  //insert_node at back of nodes
		Int_Node<T>* current = new Int_Node<T>;
		current -> next = NULL;
		current -> pre = tail;
		current -> value = value;
		tail = current;
		size++;
	}
	return true;
}

template <typename T> 
bool Link_List<T>::insert_node(int index, T value){  //inser node at somewhere
	if(index > size ){ //index is too big
		return false;
	}
	Int_Node<T>* current = new Int_Node<T>;
	current = head;
	for(int i = 0; i < index; i++){
		current = current -> next;
	}
	if(current == head){  // insert_node at first
		current -> next = head;
		current -> pre = NULL;
		current -> value = value;
		head -> pre = current;
		head = current;
		size++;
	}
	else if(current == tail){  // insert_node at last
		current -> next = NULL;
		current -> pre = tail;
		current -> value = value;
		tail -> next = current;
		tail = current;
		size++;
	}
	else{ // insert_node at middle between current and current pre
		Int_Node<T>* insert = new Int_Node<T>;
		insert -> pre = current -> pre;
		insert -> next = current;
		insert -> value = value;
		current -> pre = insert;
		current -> pre -> next = insert;
		size++;
		delete [] current; // because it's not the new value
	}
	return true;
}

template <typename T> 
bool Link_List<T>::delete_node(){  // delete the last node
	if(head == NULL){
		return false; // it doesn't have value to delete
	}
	else {
		Int_Node<T>* current = new Int_Node<T>;
		current = tail;
		tail = tail -> pre;
		tail -> next = NULL; 
		delete [] current;
		size--;
		return true;
	}
}

template <typename T> 
bool Link_List<T>::delete_node(int index){
	if(index >= size){
		return false;
	}
	Int_Node<T>* current = new Int_Node<T>;
	current = head;
	for(int i = 0; i < index; i++){
		current = current -> next;
	}
	if(current == head){ // delete node at first
		head = current -> next;
		head -> pre = NULL;
		size--;
	}
	else if(current == tail){  // delete node at last
		tail = tail -> pre;
		tail -> next = NULL;
		size--;
	}
	else{  // delete_node at middle between current and current pre
		Int_Node<T>* dele = new Int_Node<T>; 
		dele -> pre -> next = current -> next;
		dele -> next -> pre = current -> pre;
		size--;
	}
	delete [] current;
	return true;
}

template <typename U>
ostream &operator<<(ostream &s, const Link_List<U> &ll){ // operator for print all integer
	Int_Node<U>* current = new Int_Node<U>;
	current = ll.head;
	for(int i = 0; i < ll.getsize(); i++){
		s << current -> value << " ";
		current = current -> next;
	}
	cout << endl;
}

template <typename U> 
istream &operator>>(istream &s, Link_List<U> &ll){  //operator for input a value at the back of the list
	int count;
	s >> count;
	ll.insert_node(count);
}
