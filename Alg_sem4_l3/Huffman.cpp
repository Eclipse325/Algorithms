#include "pch.h"
#include "Huffman.h"
#include <iostream>
#include <string>

void Huffman::buildTree(string input)
{
	fill_list(input);

	if (list.isEmpty())
		return;

	if (list.get_size() == 1)
	{
		HuffNode* node = new HuffNode; node->freq = list.at(0)->freq;
		node->left = list.at(0); node->right = nullptr;
		list.remove(0);
		list.push_back(node);
	}

	while (list.get_size() != 1)
	{
		size_t min1, min2, index_min1, index_min2;
		min1 = list.at(0)->freq; min2 = list.at(1)->freq;
		index_min1 = 0; index_min2 = 1; // keep their index in list

		for (size_t i = 2; i < list.get_size(); i++) //find two symbols with min frequencies
		{
			size_t buff = list.at(i)->freq;
			if (buff < min1)
			{
				min1 = buff;
				index_min1 = i;
			}
			else if (buff < min2)
			{
				min2 = buff;
				index_min2 = i;
			}
		}

		HuffNode* node = new HuffNode; node->freq = min1 + min2;
		node->left = list.at(index_min1); node->right = list.at(index_min2);

		if (index_min1 > index_min2) //remove from list two nodes
		{
			list.remove(index_min1); list.remove(index_min2);
		}
		else if (index_min1 < index_min2)
		{
			list.remove(index_min2); list.remove(index_min1);
		}

		list.push_back(node);
	}
	root = list.at(0);
}

void Huffman::fill_list(string input)
{
	char symbols[255]; for (size_t i = 0; i < 255; i++) symbols[i] = 0;
	for (size_t i = 0; input[i] != '\0'; i++)
	{
		char buff = input[i];
		symbols[buff] += 1;
	}

	for (size_t i = 0; i < 255; i++)
		if (symbols[i] != 0)
		{
			HuffNode* node = new HuffNode;
			node->symbol = i; node->freq = symbols[i];
			list.push_back(node);
		}
}


void Huffman::encode(HuffNode * current)
{
	if (current == nullptr)
		return;

	if (current->left != nullptr) {
		current->left->code = current->code + "0"; encode(current->left);
	}
	
	if (current->right != nullptr) {
		current->right->code = current->code + "1"; encode(current->right);
	}
}


string Huffman::encode_string(string to_encode)
{
	buildTree(to_encode);
	encode(root);
	return decode_string(to_encode);

}

string Huffman::decode_string(string to_decode)
{
	try {
		if (root == nullptr)
			throw out_of_range("Root is nullptr");
		string decode = "";
		cout << "\nDecode " << to_decode << "\n";
		cout << "\"";
		HuffNode *current = root;
		for (size_t i = 0; i != to_decode.size(); i++)
		{
			if (to_decode[i] == '1' && current->right)
				current = current->right;
			else if (to_decode[i] == '0' && current->left)
				current = current->left;

			if (current->left == nullptr && current->right == nullptr)
			{
				cout << current->symbol;
				decode += current->symbol;
				current = root;
			}
		}
		cout << "\"";
		return decode;
	}
	catch (out_of_range) {
		return "\0";
	}
}

void Huffman::print_info(string str)
{
	try {
		if (root == nullptr)
			throw exception("Root is nullptr");
		HuffNode *current = root;
		string str_code = "";
		if (root->left && !root->right)
		{
			for (size_t i = 0; i < str.length()-1; i++)
				str_code += "0";
		}
		cout << "Symbol: " << "\t frequency: " << "\t code:" << endl;
		print(root, str_code, str, 0);
		cout << "\nHuffman's Tree:\n";
		printTree(root, 0);
		cout << "\nEncoding string is " << str_code << endl;
		cout << "\nNow string size is " << str_code.length() << endl;
		cout << "Compression ratio is " << (double) str.length()*8 / (double) str_code.length() << endl;
	}
	catch (exception) {
		return;
	}
}

void Huffman::print(HuffNode *current, string &str_code, const string &str, size_t index)
{
	if (index != str.length()) {
		if (!current->left && !current->right && current->symbol == str[index])
		{
			if(!already_was(str, index))
				cout << "  \"" << current->symbol << "\"\t           " << current->freq << "\t           " << current->code << endl;
			str_code += current->code;
			index++;
			print(root, str_code, str, index);
		}
		if (current->left)
			print(current->left, str_code, str, index);
		if (current->right)
			print(current->right, str_code, str, index);
	}
}

void Huffman::printTree(HuffNode *node, int tab)
{
	if (root == nullptr)
		cout << "Tree is empty";

	else if (node != nullptr){
		printTree(node->left, tab + 1);
		for (int k = 0; k < tab; k++) {
			cout << '\t';
		}

		cout << "\"" << node->symbol << "\" " << node->code;
		cout << endl;
		printTree(node->right, tab + 1);
	}
}