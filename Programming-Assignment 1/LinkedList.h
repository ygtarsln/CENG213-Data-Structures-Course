#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {

    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {

    size = obj.size;
    
	if (size == 0){
    	head = NULL;
	}
	
	else{
		int i = 1;
		head = new Node<T>(obj.head -> data);
		
		Node<T> *paste = head;
		Node<T> *copy = obj.head;
		
		while (i < size){
			paste -> next = new Node<T>(copy -> next -> data);
			paste -> next -> prev = paste;
			copy = copy -> next;
			paste = paste -> next;
			i++;
		}
		paste -> next = head;
		head -> prev = paste;
	}
}

template<class T>
LinkedList<T>::~LinkedList() {

	int i = 0, tmp_size = size;
	
	while (i < tmp_size){
		Node<T> *temporary = head;
		removeNode(temporary);
		i++;
	}
}

template<class T>
int LinkedList<T>::getSize() const {

    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {

    return (size == 0);
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {

    bool contain = false;
    Node<T> *current = head;
    
    if (current){
    	int i = 0;
		while (i < size){
    		
			if (current == node){
    			contain = true;
    			break;
			}
			
			current = current -> next;
			i++;
		}
	}
	
	return contain;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {

    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {

    if (!head) return head;
    
    else return head -> prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {

    Node<T> *current = head, *found = NULL;
    int i = 0;
    
    while (i < size){
    	
    	if (current -> data == data){
    		found = current;
    		break;
		}
		
		current = current -> next;
		i++;
	}
	
	return found;
    
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {

    if (index < 0 || index >= size) return NULL;
    
    else{
    	Node<T> *current = head;
    	int i = 0;
    	
    	while (i < index){
    		current = current -> next;
    		i++;
		}
		return current;
	}
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {

    if (!head){
    	head = new Node<T>(data);
    	head -> next = head;
    	head -> prev = head;
	}
	
	else{
		head = new Node<T>(data, head -> prev, head);
		head -> next -> prev -> next = head;
		head -> next -> prev = head;
	}
	
	size++;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {

    if (!head){
    	head = new Node<T>(data);
    	head -> next = head;
    	head -> prev = head;
	}
	
	else{
		head -> prev -> next = new Node<T>(data, head -> prev, head);
		head -> prev = head -> prev -> next;
	}
	
	size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {

    if (!head) return;
    
    else{
    	Node<T> *current = head;
    	int i = 0;
    	
    	while (i < size){
    		if (current == node){
    			current -> next = new Node<T>(data, current, current -> next);
    			current -> next -> next -> prev = current -> next;
    			size++;
				break; 
			}
			
			current = current -> next;
			i++;
		}
	}
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {

    if (k < 2 || !head) return;
    
    else{
    	int i = 0, j;
    	Node<T> *current = head;
    	
    	while (i < size){
    		if (i % k == k-2){
    			insertAfterNode(data, current);
    			for (j=0; j<k; j++){
    				current = current -> next;
    				i++;
				}
    			continue;
			}
			current = current -> next;
			i++;
		}
	}
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    
	if (size == 0){
		return;
	}
	
	else if (size == 1){
		if (node == head){
			delete node;
			head = NULL;
			size--;
		}
	}
	
	else if (node == head){
    	head = head -> next;
    	head -> prev = node -> prev;
		node -> prev -> next = head;
		delete node;
		size--; 
	}
	
	else{
		Node<T> *current = head -> next;
		int i = 1, tmp_size = size, found = 0;
		
		while (i < tmp_size-1){
			if (current == node){
				current -> prev -> next = current -> next;
				current -> next -> prev = current -> prev;
				delete node;
				found = 1;
				size--;
				break; 
			}
			current = current -> next;
			i++;
		}
		
		if (!found && current == node){
			current -> prev -> next = head;
			current -> next -> prev = current -> prev;
			delete node;
			size--;
		}
	}
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {

    if (size == 0){
    	return;
	}
	
	else if (size == 1){
		if(head -> data == data){
			delete head;
			head = NULL;
			size--;
		}
	}
	
	else{
		int i = 0, tmp_size = size;
		Node<T> *current = head;
		
		while (i < tmp_size){
			if (current -> data == data){
				Node<T> *temporary = current;
				current = current -> next;
				removeNode(temporary);
				i++;
				continue;
			}
			current = current -> next;
			i++;
		}
	}
}

template<class T>
void LinkedList<T>::removeAllNodes() {

    int i = 0, tmp_size = size;
    
    while (i < tmp_size){
    	removeNode(head);
    	i++;
	}
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {

    if (k < 2 || !head) return;
    
    else{
    	int i = 1;
    	Node<T> *current = head -> next;
    	
    	while (i < size){
    		if (i % k == k-1){
    			current = current -> next;
				removeNode(current -> prev);
				i++;
				continue;	
			}
			
			current = current -> next;
			i++;
		}
	}
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
 
    if (node1 == node2) return;
    
    else{
    	int node1_found = 0, node2_found = 0, node1_index, node2_index, i = 0;
    	Node<T> *current = head;
    
    	while (i < size && !(node1_found && node2_found)){
    		if (current == node1){
    			node1_found = 1;
    			node1_index = i;
			}
			else if (current == node2){
				node2_found = 1;
				node2_index = i;
			}
		
			current = current -> next;
			i++;
		}
		
		if (node1_found && node2_found){
			if (node2_index - node1_index == 1 || (node2_index == 0 && node1_index == size-1)){
				node1 -> next = node2 -> next;
				node2 -> next = node1;
				node2 -> prev = node1 -> prev;
				node2 -> prev -> next = node2;
				node1 -> prev = node2;
				node1 -> next -> prev = node1;
				
				if (node1_index == 0) head = node2;
				if (node2_index == 0 && node1_index == size-1) head = node1; 
			}
			
			else if (node1_index - node2_index == 1 || (node1_index == 0 && node2_index == size-1)){
				node2 -> next = node1 -> next;
				node1 -> next = node2;
				node1 -> prev = node2 -> prev;
				node1 -> prev -> next = node1;
				node2 -> prev = node1;
				node2 -> next -> prev = node2;
				
				if (node2_index == 0) head = node1;
				if (node1_index == 0 && node2_index == size-1) head = node2;
			}
			
			else if (node2_index - node1_index > 1){
				Node<T> *tmp1 = node1 -> next, *tmp2 = node2 -> prev;
				node1 -> next = node2 -> next;
				node2 -> prev = node1 -> prev;
				node1 -> prev = tmp2;
				node2 -> next = tmp1;
				node2 -> prev -> next = node2;
				node1 -> next -> prev = node1;
				tmp1 -> prev = node2;
				tmp2 -> next = node1;
				
				if (node1_index == 0) head = node2; 
			}
			
			else if (node1_index - node2_index > 1){
				Node<T> *tmp1 = node1 -> prev, *tmp2 = node2 -> next;
				node2 -> next = node1 -> next;
				node1 -> prev = node2 -> prev;
				node2 -> prev = tmp1;
				node1 -> next = tmp2;
				node1 -> prev -> next = node1;
				node2 -> next -> prev = node2;
				tmp2 -> prev = node1;
				tmp1 -> next = node2;
				
				if (node2_index == 0) head = node1;
			}
		}
	}
}

template<class T>
void LinkedList<T>::shuffle(int seed) {

    int i;
    Node<T> *swap1, *swap2;
    
    for (i = 0; i < size; i++){
    	swap1 = getNodeAtIndex(i);
    	swap2 = getNodeAtIndex((i*i+seed) % size);
    	swap(swap1, swap2);
		
	}
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {

    if (this != &rhs){
    	
		Node<T> *copy = rhs.head;
    	int i = 0;
		
		removeAllNodes();
		
		while (i < rhs.size){
			insertAtTheEnd(copy -> data);
			copy = copy -> next;
			i++;
		}
    	
	}
	
	return *this;
}

#endif //LINKEDLIST_H
