#include "pch.h"
#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"
#include <cstdlib>
#include <Windows.h>
using namespace std;

void text()
{
	cout << "Laboratory work №1 \"List template class\"\nKarmanov D. gr.7302 var. 2\n";
	cout << "\n1. Add an item into the end of the list\n";
	cout << "2. Add an item into the beginning of the list\n";
	cout << "3. Remove the last list item \n";
	cout << "4. Remove the first list item\n";
	cout << "5. Add an item by index\n";
	cout << "6. Get an item by index\n";
	cout << "7. Remove an item by index\n";
	cout << "8. Get the list size\n";
	cout << "9. Print list items\n";
	cout << "10. Clear the list\n";
	cout << "11. Replace an item by index with transmitted\n";
	cout << "12. Is the list empty?\n";

	cout << "\nAdditional function:\n-1. Close the programm\n-2. Clear extra text\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	LinkedList<double> lst;
	int t;
	text();

	do {
		double value;
		int index;
		int index1;
		cout << "\nEnter option: "; cin >> t;
		switch (t)
		{
		case -2: system("cls"); text(); break;
		case -1: break;
		case 1: cout << "Enter the item value: "; cin >> value; lst.push_back(value); break;
		case 2: cout << "Enter the item value: "; cin >> value; lst.push_front(value); break;
		case 3: lst.pop_back(); break;
		case 4: lst.pop_front(); break;
		case 5: cout << "Enter the value: "; cin >> value; cout << "Enter the index: "; cin >> index; lst.insert(index, value); break;
		case 6: cout << "Enter the index: "; cin >> index; cout << lst.at(index) << endl; break;
		case 7: cout << "Enter the index: "; cin >> index; lst.remove(index); break;
		case 8: cout << "List size is " << lst.get_size() << endl; break;
		case 9: cout << lst; break;
		case 10: lst.clear(); break;
		case 11: cout << "\nEnter the value: "; cin >> value; cout << "Enter the index: "; cin >> index; lst.set(index, value); break;
		case 12: (lst.isEmpty() == 0) ? cout << "No" : cout << "Yes"; cout << endl; break;
		}
	} while (t != -1);
	system("cls");

	cout << "\nBon Voyage!\n";

	return 0;
}
