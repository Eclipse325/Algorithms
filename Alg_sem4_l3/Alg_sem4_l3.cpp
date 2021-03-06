#include "pch.h"
#include <iostream>
#include "Huffman.h"

int main()
{
	cout << "Karmanov D., gr.7302, lab.3 \"Huffman's algorithm\"\n";
	Huffman huff;
	string str;
	cout << "\nEnter the string: ";
	getline(cin, str);
	cout << "Current line size is " << str.size() * 8 << endl;
	huff.encode_string(str);
	huff.print_info(str);
	string decode = huff.decode_string("10010");
	cout << "\nDecoding string is \"" << decode << "\"" << endl;
}