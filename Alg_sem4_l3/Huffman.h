#pragma once
#include "..//Alg_sem4_l1/LinkedList.h"
#include "..//Alg_sem4_l1/LinkedList.cpp"

class Huffman;

class HuffNode
{
	char symbol{};
	size_t freq{};
	string code{};

	HuffNode *left{};
	HuffNode *right{};

	friend Huffman;
public:
	HuffNode()
	{
		freq = 0;
		symbol = 0;
		left = nullptr;
		right = nullptr;
	};
	~HuffNode()
	{
		freq = 0;
		symbol = 0;
		left = nullptr;
		right = nullptr;
		delete this;
	};
};

class Huffman
{
	HuffNode* root{};
	LinkedList<HuffNode*> list;
	void buildTree(string input); //create Huffman's tree
	void fill_list(string input); //create HuffNodes and count frequency
	void encode(HuffNode* current); //encode symbols
	void print(HuffNode*, string&, const string&, size_t index);
	void printTree(HuffNode*, int);
	bool already_was(string str, size_t index) { //Was this symbol?
		size_t i = 0;
		for (i; i < str.length(); i++)
		{
			if (str[i] == str[index] && i < index) return true;
		}
		return false;
	};

public:
	string encode_string(string to_encode);
	string decode_string(string to_decode);
	void print_info(string str); //symbol, frequency, and aspect ratio
	~Huffman()
	{
		list.~LinkedList();
		root = nullptr;
	};
};