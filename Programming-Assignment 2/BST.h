#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    bool contains(BSTNode<T> *rt, BSTNode<T> *node) const;
    void insert(BSTNode<T> *&rt, const T &data);
    BSTNode<T> *search(BSTNode<T> *rt, const T &data) const;
    void remove(BSTNode<T> *&rt, const T &data);
    T findmin(BSTNode<T> *rt) const;
    void removeAllNodes(BSTNode<T> *&rt);
    BSTNode<T> *findParent(BSTNode<T> *rt, BSTNode<T> *node) const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    
    BSTNode<T> *objroot = obj.getRoot();
    root = NULL;
    
    if (objroot){
    	
		BSTNode<T> *preorder_successor = obj.getSuccessor(objroot, preorder);
		insert(root, objroot -> data);
		
		while (preorder_successor != NULL){
    		insert(root, preorder_successor -> data);
    		preorder_successor = obj.getSuccessor(preorder_successor, preorder);
		}
	}    
}

template<class T>
BST<T>::~BST() {
    removeAllNodes();
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    return (root == NULL);
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    return contains(root, node);
}

template<class T>
void BST<T>::insert(const T &data) {
    insert(root, data);
}

template<class T>
void BST<T>::remove(const T &data) {
    remove(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    removeAllNodes(root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    return search(root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {

    if (tp == inorder) {
        
        if (node -> right) return search(findmin(node -> right));
        
        else{
        	BSTNode<T> *parent = findParent(root, node);
        	
        	if (parent == NULL){
        		return NULL;
			}
			
			else{
				BSTNode<T> *temp = node;
				
				while (parent && parent ->  left != temp){
					temp = parent;
					parent = findParent(root, temp);
				}
				
				return parent;	
			}	
		}   
    } else if (tp == preorder) {
        
		if (node -> left) return node -> left;
        
		else if (node -> right) return node -> right;
        
		else{
			BSTNode<T> *parent = findParent(root, node);
			
			
			if (parent == NULL){ // BST consists of one node, namely the root
				return NULL;
			}
			
			else{
				BSTNode<T> *temp = node;
				
				while (parent && (parent -> right == NULL || parent -> right == temp)){    // while parent doesnt have a right child or its right child is temp
					temp = parent;
					parent = findParent(root, temp);
				}
			
			if (parent) return parent -> right;
			else return NULL;
			}
		}        
        
        
    } else if (tp == postorder) {
        BSTNode<T> *parent = findParent(root, node);
        
        if (parent == NULL){
        	return NULL;
		}
		
		else{
			if (parent -> right == node || parent -> right == NULL) return parent;
			else{
				BSTNode<T> *temp = parent -> right;
				
				while (temp -> right != NULL || temp -> left != NULL){
					if (temp -> left) temp = temp -> left;
					else temp = temp -> right;
				}
				
				return temp;
			}
		}
    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
    	
		if (isEmpty()){
    		std::cout << "BST_preorder{}" << std::endl;
    		return;
		}
		
		std::cout << "BST_preorder{" << std::endl;
		print(root, preorder);
		std::cout << std::endl << "}" << std::endl;
		
    } else if (tp == postorder) {
    	
    	if (isEmpty()){
    		std::cout << "BST_postorder{}" << std::endl;
    		return;
		}
		
		std::cout << "BST_postorder{" << std::endl;
		print(root, postorder);
		std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    if (this != &rhs){
    	removeAllNodes();
    	
    	BSTNode<T> *rhsroot = rhs.getRoot();
    
    	if (rhsroot){
    	
			BSTNode<T> *preorder_successor = rhs.getSuccessor(rhsroot, preorder);
			insert(root, rhsroot -> data);
		
			while (preorder_successor != NULL){
    			insert(root, preorder_successor -> data);
    			preorder_successor = rhs.getSuccessor(preorder_successor, preorder);
			}
		}
	}
	
	return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        
        std::cout << "\t" << node -> data;
        
        if (node -> left){
        	std::cout << "," << std::endl;
		}
		print(node -> left, preorder);
		
		if (node -> right){
			std::cout << "," << std::endl;
		}
		print(node -> right, preorder);
        
    } else if (tp == postorder) {
		
		print(node -> left, postorder);
		if (node -> left){
			std::cout << "," << std::endl;
		}
		
		print(node -> right, postorder);	
		if (node -> right){
			std::cout << "," << std::endl;
		}
		
		std::cout << "\t" << node -> data;	
    }
}

template<class T>
bool BST<T>::contains(BSTNode<T> *rt, BSTNode<T> *node) const{

	if (!rt) return false;
	
	if (root == node) return true;
	
	return contains(rt -> left, node) || contains(rt -> right, node);
}

template<class T>
void BST<T>::insert(BSTNode<T> *&rt, const T &data){
	
	if (!rt){
		rt = new BSTNode<T>(data, NULL, NULL);
		return;
	}
	
	else if (data < rt -> data){
		insert(rt -> left, data);
	}
	
	else{
		insert(rt -> right, data);
	}
}

template<class T>
BSTNode<T> *BST<T>::search(BSTNode<T> *rt, const T &data) const{
	
	if (!rt) return NULL;
	
	if (rt -> data == data) return rt;
	
	else if (data < rt -> data){
		return search(rt -> left, data);
	}
	
	else if (data > rt -> data){
		return search(rt -> right, data);
	}
}

template<class T>
void BST<T>::remove(BSTNode<T> *&rt, const T &data){
	
	if (!rt) return;
	
	else if (rt -> data == data){
		
		if (!(rt -> left) && !(rt -> right)){
			delete rt;
			rt = NULL;
		}
		
		else if (!(rt -> left)){
			BSTNode<T> *tmp = rt;
			rt = rt -> right;
			delete tmp;
		}
		
		else if (!(rt -> right)){
			BSTNode<T> *tmp = rt;
			rt = rt -> left;
			delete tmp;
		}
		
		else{
			rt -> data = findmin(rt -> right);
			remove(rt -> right, rt -> data);
		}
		
		return;
	}
	
	else if (data < rt -> data){
		remove(rt -> left, data);
	}
	
	else if (data > rt -> data){
		remove(rt -> right, data);
	}
}

template<class T>
T BST<T>::findmin(BSTNode<T> *rt) const{
	
	if (!(rt -> left)) return rt -> data;
	
	return findmin(rt -> left);
}

template<class T>
void BST<T>::removeAllNodes(BSTNode<T> *&rt){
	
	if (!rt) return;
	
	if (!(rt -> left) && !(rt -> right)){
		delete rt;
		rt = NULL;
		return;
	}
	
	removeAllNodes(rt -> left);
	removeAllNodes(rt -> right);
	delete rt;
	rt = NULL;
}

template<class T>
BSTNode<T> *BST<T>::findParent(BSTNode<T> *rt, BSTNode<T> *node) const{
	
	if (rt == node) return NULL;
	
	if (rt -> left == node || rt -> right == node) return rt;
	
	else if (node -> data > rt -> data){
		return findParent(rt -> right, node);
	}
	
	else if (node -> data < rt -> data){
		return findParent(rt -> left, node);
	}
}
