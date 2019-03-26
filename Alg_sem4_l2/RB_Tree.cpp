#include "pch.h"
#include "RB_Tree.h"
#include <iostream>
#include <string>

using namespace std;

template <class T, class G>
RB_Tree<T, G>::RB_Tree()
{
	size = 0;
	root = nullptr;
}

template <class T, class G>
RB_Tree<T, G>::~RB_Tree()
{
	clear();
}

template <class T, class G>
RB_Tree<T, G>::Node::Node(T key, G value, bool color, Node *right, Node *left)
{
	this->value = value;
	this->key = key;
	p = nullptr;
}

template <class T, class G>
RB_Tree<T, G>::Node::~Node()
{
	value = {};
	p = left = right = nullptr;
	color = 1;
}

template <class T, class G>
void RB_Tree<T, G>::insert(T key, G value)
{
	Node *t = new Node(key, value, 0, nullptr, nullptr);
	if (size == 0) {
		root = t;
		t->p = nullptr;
	}
	else {
		try {
			Node *ptr = root;
			Node *q = nullptr;
			while (ptr != nullptr) {
				q = ptr;
				if (ptr->key != t->key) {
					if (ptr->key < t->key)
						ptr = ptr->right;
					else
						ptr = ptr->left;
				}
				else
					throw exception ("Already exists");
			}
			t->p = q;
			if (q->key < t->key)
				q->right = t;
			else
				q->left = t;
		}
		catch (exception)
		{
			delete t;
			return;
		}
	}
	size++;
	insert_case1(t);
}

template <class T, class G>
void RB_Tree<T, G>::insert_case1(Node *n)
{
	if (n->p == nullptr)
		n->color = 1;
	else insert_case2(n);
}

template <class T, class G>
void RB_Tree<T, G>::insert_case2(Node *n)
{
	if (n->p->color == 1)
		return;
	else insert_case3(n);
}

template <class T, class G>
void RB_Tree<T, G>::insert_case3(Node *n)
{
	Node *u = uncle(n);
	if ((u != nullptr) && (u->color == 0)) {
		n->p->color = 1;
		u->color = 1;
		grandparent(n)->color = 0;
		insert_case1(grandparent(n));
	}
	else insert_case4(n);
}

template <class T, class G>
void RB_Tree<T, G>::insert_case4(Node *n)
{
	Node *g = grandparent(n);
	if ((n == n->p->right) && (n->p == g->left)) {
		rotateLeft(n->p);
		n = n->left;
	}
	else if ((n == n->p->left) && (n->p == g->right)) {
		rotateRight(n->p);
		n = n->right;
	}
	insert_case5(n);
}

template <class T, class G>
void RB_Tree<T, G>::insert_case5(Node *n)
{
	Node *g = grandparent(n);
	n->p->color = 1;
	g->color = 0;
	if ((n == n->p->left) && (n->p == g->left))
		rotateRight(g);
	else rotateLeft(g);
}


template <class T, class G>
void RB_Tree<T, G>::clear() 
{
	clear(root);
}

template <class T, class G>
void RB_Tree<T, G>::remove(T key)
{	
	Node *n = find(key);
	if (n != nullptr) {
		if (n == root && size == 1)
		{
			delete n;
			root = nullptr;
			size--;
			return;
		}
		Node *temp = n;
		if (temp->left && temp->right) {
			temp = temp->right;
			while (temp->left) temp = temp->left;
			if (!temp->left && temp->right) {
				swap(temp, temp->right); temp = temp->right;
			}
		}
		else
			while (temp->left || temp->right) {
				if (temp->left) temp = temp->left;
				else temp = temp->right;
			}
		swap(n, temp);
		delete_one_child(temp);
		size--;
	}
}

template <class T, class G>
void RB_Tree<T, G>::delete_one_child(Node *n)
{
	if (n->p) {
		if (!n->left && !n->right) {
			if (n->color == 1 && !sibling(n) && n->p->color == 0)
				n->p->color = 1;
			else if (n->p->color == 0 && n->color == 1 && sibling(n) && sibling(n)->color == 1) {
				n->p->color = 1;
				sibling(n)->color = 0;
			}
			else if (n->p->color == 1 && n->color == 1 && sibling(n) && sibling(n)->color == 1)
				delete_case1(n);
			else if (n->p->color == 1 && n->color == 1 && sibling(n) && sibling(n)->color == 0)
				delete_case1(n);
		}
		if (n == n->p->left) n->p->left = nullptr;
		else n->p->right = nullptr;
		n->p = nullptr;
		delete n;
		n = nullptr;
	}
}

template <class T, class G>
void RB_Tree<T, G>::delete_case1(Node *n)
{
	if (n->p != nullptr)
		delete_case2(n);
}

template <class T, class G>
void RB_Tree<T, G>::delete_case2(Node *n)
{
	Node *s = sibling(n);
	if (s && s->color == 0) {
		n->p->color = 0;
		s->color = 1;
		if (n == n->p->left)
			rotateLeft(n->p);
		else
			rotateRight(n->p);
	}
	delete_case3(n);
}

template <class T, class G>
void RB_Tree<T, G>::delete_case3(Node *n)
{
	Node *s = sibling(n);
	if ((n->p->color == 1) && (s && s->color == 1) && 
		(!s->left || (s->left && s->left->color == 1)) && 
		(!s->right || (s->right &&s->right->color == 1)))
	{
		s->color = 0;
		delete_case1(n->p);
	}
	else delete_case4(n);
}

template <class T, class G>
void RB_Tree<T, G>::delete_case4(Node *n)
{
	Node *s = sibling(n);

	if ((n->p->color == 0) && (s && s->color == 1) 
		&& (!s->left || (s->left && s->left->color == 1)) 
		&& (!s->right || (s->right && s->right->color == 1)))
	{
		s->color = 0;
		n->p->color = 1;
	}
	else delete_case5(n);
}

template <class T, class G>
void RB_Tree<T, G>::delete_case5(Node *n)
{
	Node *s = sibling(n);
	if (s && s->color == 1) {
		if ((n == n->p->left) && (!s->right || (s->right && s->right->color == 1)) && (s->left && s->left->color == 0)) {
			s->color = 0;
			s->left->color = 1;
			rotateRight(s);
		}
		else if ((n == n->p->right) && (!s->left || (s->left && s->left->color == 1)) 
			&& (s->right && s->right->color == 0)) {
			s->color = 0;
			s->right->color = 1;
			rotateLeft(s);
		}
	}
	delete_case6(n);
}

template <class T, class G>
void RB_Tree<T, G>::delete_case6(Node *n)
{
	Node *s = sibling(n);
	if (s) {
		s->color = n->p->color;
		n->p->color = 1;
		if (n == n->p->left) {
			s->right->color = 1;
			rotateLeft(n->p);
		}
		else {
			s->left->color = 1;
			rotateRight(n->p);
		}
	}
}


template <class T, class G>
LinkedList<T>* RB_Tree<T, G>::get_keys()
{
	LinkedList<T> *lstKey = new LinkedList<T>;
	if (size != 0) {
		auto *iter = create_dft_iterator();
		while (iter->has_next())
			lstKey->push_front(iter->next()->key);
	}
	return lstKey;
};

template <class T, class G>
LinkedList<G>* RB_Tree<T, G>::get_values()
{
	LinkedList<G> *lstVal = new LinkedList<G>;
	if (size != 0) {
		auto *iter = create_dft_iterator();
		while (iter->has_next())
			lstVal->push_front(iter->next()->value);
	}
	return lstVal;
};

template <class T, class G>
void RB_Tree<T, G>::print(Node *node, long tab)
{
	if (root == nullptr)
		cout << "Tree is empty";

	else if (node != nullptr) {
		print(node->left, tab + 1);
		for (int k = 0; k < tab; k++) {
			cout << '\t';
		}

		if (node->p != nullptr && node == node->p->left) cout << "L: ";
		else if (node->p != nullptr && node == node->p->right) cout << "R: ";
		cout << node->key;
		if (node->color == 1) cout << "(B)";
		else cout << "(R)";
		cout << endl;
		print(node->right, tab + 1);
	}
}


template <class T, class G>
bool RB_Tree<T, G>::are_equal_keys(T *a1, T *a2, int s1, int s2)
{
	for (int i = 0; i < s1, i < s2; i++)
		if (a1[i] != a2[i]) return false;
	return true;
}

template <class T, class G>
bool RB_Tree<T, G>::are_equal_colors(bool *a1, bool *a2, int s1, int s2)
{
	for (int i = 0; i < s1, i < s2; i++)
		if (a1[i] != a2[i]) return false;
	return true;
}