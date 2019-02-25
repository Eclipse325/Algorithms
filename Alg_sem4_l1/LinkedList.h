#pragma once
#include "Iterator.h"
#include <iostream>

template <typename T>
class LinkedList 
{
public:
	class Node
	{
	public:
		Node(T data, Node *next = nullptr, Node * prev = nullptr) {
			this->data = data;
			this->next = next;
			this->prev = prev;
		};
		~Node() {
			next = nullptr;
			delete next;
			prev = nullptr;
			delete prev;
			data = {};
		}

		T data;
		Node *next;
		Node *prev;
	};
	void reset_list();

	Node *head{};
	Node *tail{};
	size_t size;

	class ListIterator : public Iterator<T>
	{
	public:
		ListIterator(Node *head) { current = head; };
	private:
		T next() override;
		bool has_next() override;
		Node* current;
	};

	Iterator<T>* create_list_iterator();
	friend std::ostream& operator<<(std::ostream& os, LinkedList<T>& linked_list) {
		if (linked_list.size == 0)
			return os << "[nullptr]";
		auto* list = linked_list.create_list_iterator();
		os << "[nullptr] <-> ";
		while (list->has_next()) {
			os << "[" << list->next() << "] <-> ";
		}
		os << "[nullptr]" << std::endl;
		return os;
	};

public:
	LinkedList();
	~LinkedList();
	void push_back(T newElem); //Add an item into the end
	void push_front(T newElem); //Add an item into the beginning
	void pop_back(); //Remove an item from the end
	void pop_front(); //Remove an item from the beginning
	void insert(size_t index, T newElem); //Add an item into the list by index
	T at(size_t index); //Get an item by index
	void remove(size_t index); //Remove an item by index
	size_t get_size(); //Get list size
	void clear(); //Remove all items from the list
	void set(size_t index, T newElem); //Set new item value by index
	bool isEmpty(); //Is list empty?
};
