#pragma once
#include <string>
#include <queue>
#include <iostream>
#include "..//Alg_sem4_l1/LinkedList.h"
#include "..//Alg_sem4_l1/LinkedList.cpp"	

using namespace std;

/*n - node
  p - parent
  g - grandparent
  u - uncle*/


template <class T, class G>
class RB_Tree
{
public:
	class Node
	{
	public:
		Node(T key, G value, bool color, Node *right, Node *left);
		~Node();

	public:
		G value;
		T key;
		Node *p = {};
		Node *right = {};
		Node *left = {};
		bool color; //1 - black, 0 - red;
	}; 

public:
	class Iterator
	{
	public:
		virtual Node* next() = 0;
		virtual bool has_next() = 0;
	};

	class DFT_Iterator : public Iterator
	{
	public:
		DFT_Iterator(Node *root) {
			current = root;
		};
		Node* next() {
			if (current != nullptr) {
				Node* n = current;
				if (current->right != nullptr)
					q.push(current);
				current = current->left;
				return n;
			}
			if (current == nullptr) {
				current = q.front();
				q.pop();
				current = current->right;
				next();
			}
		}
		bool has_next() {
			return (q.size() || current != nullptr);
		};

	private:
		queue<Node*> q;
		Node* current;
	};

	Node *root;
	size_t size;

	RB_Tree();
	~RB_Tree();
	void insert(T key, G value); //To add the node to tree
	void remove(T key); // remove the node from tree
	Node* find(T key) {
		if (root != nullptr) {
			Node *temp = root;
			while (temp != nullptr || temp->key != key)
			{
				if (key > temp->key) {
					if(temp->right != nullptr)
						temp = temp->right;
					else {
						cout << "\nThe item with the key \"" << key << "\" was not found\n"; return nullptr;
					}
				}
				else if (temp->key >= key) {
					if (temp->key == key) {
						cout << "\nThe item with the key \"" << temp->key << "\" was found\n"; return temp;
					}
					if(temp->left != nullptr)
						temp = temp->left;
					else {
						cout << "\nThe item with the key \"" << key << "\" was not found\n"; return nullptr;
					}
				}
			}
		}
		return nullptr;
	}; //find the node in tree
	void clear(); //delete the tree
	void print(Node *n, long tab); //print the tree
	LinkedList<T>* get_keys(); //return the keys' list
	LinkedList<G>* get_values(); //return the values' list

	Iterator* create_dft_iterator() {
		return new DFT_Iterator(root);
	};

public:
	Node* grandparent(Node *n) {
		if ((n != nullptr) && (n->p != nullptr))
			return	n->p->p;
		else return nullptr;
	};//find the node's grandparent
	Node* uncle(Node *n) {
		Node *g = grandparent(n);
		if (g == nullptr)
			return nullptr;
		if (n->p == g->left)
			return g->right;
		else return g->left;
	};//find the node's uncle
	Node* sibling(Node *n)
	{
		if (n->p) {
			if (n == n->p->left)
				return n->p->right;
			else return n->p->left;
		}
	}//find the node's brother
	void rotateLeft(Node *n) {
		Node *pivot = n->right;
		pivot->p = n->p;
		if (n->p != nullptr) {
			if (n->p->left == n)
				n->p->left = pivot;
			else n->p->right = pivot;
		}
		n->right = pivot->left;
		if (pivot->left != nullptr)
			pivot->left->p = n;

		n->p = pivot;
		pivot->left = n;
		if (pivot->p == nullptr)
			root = pivot;
	};
	void rotateRight(Node *n) {
		Node *pivot = n->left;
		pivot->p = n->p;
		if (n->p != nullptr) {
			if (n->p->right == n)
				n->p->right = pivot;
			else n->p->left = pivot;
		}
		n->left = pivot->right;
		if (pivot->right != nullptr)
			pivot->right->p = n;
		n->p = pivot;
		pivot->right = n;
		if (pivot->p == nullptr)
			root = pivot;
	}
	void insert_case1(Node *n);//if node is root
	void insert_case2(Node *n);//if the parent of node is black
	void insert_case3(Node *n);//if parent and uncle of node are red 
	void insert_case4(Node *n);//if parent is red, but uncle is black, and node is right child of his parent and 
								//his parent is left child of grandparent
	void insert_case5(Node *n);//if parent is red, but uncle is black, and node is left child of his parent and 
								//his parent is left child of grandparent
	
	void delete_one_child(Node *n); //remove leaf of the tree
	void delete_case1(Node *n); //we deleted black node and recolored his parent in black
	void delete_case2(Node *n); //sibling is red
	void delete_case3(Node *n); //parent, sibling and siblings' children are black
	void delete_case4(Node *n); //sibling and siblings' children are black, parent is red
	void delete_case5(Node *n); //sibling is black, his left is red and right is black and node is left	
								//of his parent
	void delete_case6(Node *n); //sibling is black, his right is red, node is left of his parent
	void swap(Node *n1, Node *n2)
	{   
		T tempKey = n2->key;
		G tempValue = n2->value;
		n2->key = n1->key;
		n2->value = n1->value;
		n1->key = tempKey;
		n1->value = tempValue;
	};
	void clear(Node *n) {
		if (n) {
			if (n->left) clear(n->left);
			if (n->right) clear(n->right);
			if (n == root) {
				delete root; root = nullptr; size--; return;
			}
			if (n == n->p->left) n->p->left = nullptr;
			else n->p->right = nullptr;
			n->p = nullptr;
			delete n;
			n = nullptr;
			size--;
		}
	};
	bool are_equal_keys(T*, T*, int, int);
	bool are_equal_colors(bool *, bool *, int, int);
};