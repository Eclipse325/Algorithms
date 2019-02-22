#include "pch.h"
#include <iostream>
#include "LinkedList.h"
using namespace std;

template <class T>
void LinkedList<T>::reset_list()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <class T>
void LinkedList<T>::add_first(T newElem)
{
	head = new Node(newElem);
	tail = head;
}

template <class T>
LinkedList<T>::LinkedList()
{
	reset_list();
}

template <class T>
LinkedList<T>::~LinkedList()
{
	reset_list();
}

template <class T>
void LinkedList<T>::push_back(T newElem)
{
	if (size == 0) {
		head = new Node(newElem);
		tail = head;
		head->next = nullptr;
		head->prev = nullptr;
		tail->next = nullptr;
		tail->prev = nullptr;
	}
	else {
		tail->next = new Node(newElem);
		tail->next->prev = tail;
		tail->next->next = nullptr;
		tail = tail->next;
	}
	size++;
}

template <class T>
void LinkedList<T>::push_front(T newElem)
{
	if (size == 0) {
		head = new Node(newElem);
		tail = head;
		head->next = nullptr;
		head->prev = nullptr;
	}
	else {
		head->prev = new Node(newElem);
		head->prev->next = head;
		head->prev->prev = nullptr;
		head = head->prev;
	}
	size++;
}

template <class T>
void LinkedList<T>::pop_back()
{
	if (size == 0) cout << "\nНечего удалять, список пуст\n";
	if (size == 1) {
		delete tail; tail = head = nullptr;
		size--;
	}
	if (size > 1) {
		if (tail->prev != nullptr)
			tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
		size--;
	}
}

template <class T>
void LinkedList<T>::pop_front()
{
	if (size == 0) return;

	if (size == 1) {
		reset_list();
		delete head;
		delete tail;
	}
	else {
		Node * current = head->next;
		delete head;
		head = current;
		size--;
	}
}

template <class T>
void LinkedList<T>::insert(size_t index, T newElem)
{
	if (index >= size) {
		index = size - 1;
		cout << "Индекс больше, чем наибольший индекс списка. Введенный индекс приведен к максимальному индексу списка";
	}

	if (size == 0)
	{
		head = new Node(newElem);
		tail = head;
		head->next = nullptr;
		head->prev = nullptr;
		tail->next = nullptr;
		tail->prev = nullptr;
		size++;
	}

	else {
		Node *current = head;
		size_t counter = 0;
		while (counter != index)
		{
			current = current->next;
			counter++;
		}

		Node *newElement = new Node(newElem);

		if (head != nullptr) {
			newElement->prev = current->prev;
			newElement->next = current;
			if (current->prev != nullptr)
				current->prev->next = newElement;
			current->prev = newElement;
			if (newElement->prev == nullptr)
				head = newElement;
			if (newElement->next == nullptr)
				tail = newElement;
			size++;
		}
	}
}

template <class T>
T LinkedList<T>::at(size_t index)
{
	if (index >= size)
		throw out_of_range("Индекс больше, чем наибольший индекс списка");
	else {
		Node *current = head;
		size_t counter = 0;
		while (counter != index)
		{
			current = current->next;
			counter++;
		}
		return current->data;
	}
}

template <class T>
void LinkedList<T>::remove(size_t index)
{
	if (index >= size)
		throw out_of_range("Index is greater than list size");
	Node *current = head;
	size_t counter = 0;
	while (counter != index)
	{
		current = current->next;
		counter++;
	}
	if (current->prev != nullptr)
		current->prev->next = current->next;
	if (current->next != nullptr)
		current->next->prev = current->prev;
	if (current->prev == nullptr)
		head = current->next;
	if (current->next == nullptr)
		tail = current->prev;
	current->next = nullptr; current->prev = nullptr;
	size--;
	delete current;
}

template <class T>
size_t LinkedList<T>::get_size()
{
	return size;
}

template <class T>
void LinkedList<T>::clear()
{
	if (size == 0) return;

	if (size == 1) {
		remove(0); return;
	}
	else {
		while (head != nullptr) {
			pop_front();
		}
		reset_list();
		delete head;
		delete tail;
	}
}

template <class T>
void LinkedList<T>::set(size_t index, T newElem)
{
	if (index >= size) {
		throw std::out_of_range("Index is greater than list size");
	}
	else {
		size_t counter = 0;
		Node * current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		current->data = newElem;
	}
}

template <class T>
bool LinkedList<T>::isEmpty()
{
	bool check = false;
	if (size == 0)
		check = true;
	return check;
}

template <class T>
void LinkedList<T>::swap(size_t index1, size_t index2)
{
	if (size != 0) {
		Node *current1 = head;
		Node *current2 = head;
		int counter = 0;
		int min, max;
		if (index1 >= index2) {
			max = index1; min = index2;
		}
		else {
			max = index2; min = index1;
		}
		while (counter < min)
		{
			if (current1->next != nullptr)
				current1 = current1->next;
			counter++;
		}
		current2 = current1;
		while (counter < max && current2 != nullptr)
		{
			if (current2->next != nullptr)
				current2 = current2->next;
			counter++;
		}
		int temp;
		temp = current1->data;
		current1->data = current2->data;
		current2->data = temp;
	}
	else cout << "\nСписок пуст, нечего обменивать\n";
}

template <typename T>
T LinkedList<T>::ListIterator::next()
{
	if (!current) return T();
	const T data = current->data;
	current = current->next;
	return data;
}

template <class T>
bool LinkedList<T>::ListIterator::has_next()
{
	return (current != nullptr);
}

template <class T>
Iterator<T>* LinkedList<T>::create_list_iterator() 
{
	if (this == nullptr && this->head == nullptr) throw std::exception("Does not exist");
	return new ListIterator(this->head);
}

