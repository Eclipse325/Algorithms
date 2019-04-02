#include "pch.h"
#include "Map.cpp"
#include <string>
#include <iostream>
using namespace std;


int main()
{
	cout << "Laboratory work #2 \"Associative array\"\nKarmanov D. gr.7302 var. 2\n";
	Map<string, double> tree;

	tree.insert("January", 15);
	tree.insert("February", 6);
	tree.insert("March", 9);
	tree.insert("April", 5);
	tree.insert("May", 8);
	tree.insert("June", 15);
	tree.print(); cout << "\n\n\n";
	tree.insert("Jule", 1);
	tree.insert("Ma", 23);
	tree.print(); cout << "\n\n\n";
	//tree.remove("May");
	tree.clear();
	tree.print();

	cout << "\nBon Voyage!\n";
	return 0;
}
