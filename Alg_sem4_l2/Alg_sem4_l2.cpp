#include "pch.h"
#include "RB_Tree.cpp"
#include <string>
#include <iostream>
using namespace std;


int main()
{
	cout << "Laboratory work #2 \"Associative array\"\nKarmanov D. gr.7302 var. 2\n";
	RB_Tree<string, double> tree;
	/*tree.insert("January", 15);
	tree.insert("February", 6);
	tree.insert("March", 9);
	tree.insert("April", 5);
	tree.insert("May", 8);
	tree.insert("June", 15);
	tree.insert("Jule", 1);
	tree.insert("Cucumber", 133);
	tree.print(tree.root, 0);
	tree.remove("May");
	tree.print(tree.root, 0);*/

	tree.insert("January", 15);
	tree.insert("February", 6);
	tree.insert("March", 9);
	tree.insert("April", 5);
	tree.insert("May", 8);
	tree.insert("June", 15);
	tree.insert("Jule", 1);
	tree.print(tree.root, 0);
	tree.remove("Jule"); //it is red node*/
	tree.remove("June");
	cout << *tree.get_keys() << endl;
	/*tree.insert("January", 15);
	tree.insert("February", 6);
	tree.insert("March", 9);
	tree.insert("April", 5);  // BUT HERE ALL RIGHT
	cout << "ROOT IS " << tree.root->key;*/
	tree.print(tree.root, 0);

	/*cout << "\nNOW IT IS\n";
	string *a2 = new string[6];
	auto *iter = tree.create_dft_iterator();
	int i = 0;
	while (iter->has_next()) {
		string kek = iter->next()->key;
		a2[i] = kek;
		//cout << a2[i] << " ";
		i++;
	}

	for (int i = 0; i < 6; i++)
		cout << a2[i] << " "*/

	tree.clear();
	//tree.print(tree.root, 0);

	cout << "\nBon Voyage!\n";
	return 0;
}