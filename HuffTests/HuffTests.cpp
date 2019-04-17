#include "stdafx.h"
#include "CppUnitTest.h"
#include "..//Alg_sem4_l3/Huffman.h"
#include "..//Alg_sem4_l3/Huffman.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HuffTests
{		
	TEST_CLASS(HuffTests)
	{
	public:
		
		TEST_METHOD(fill_list_empty)
		{
			Huffman huff;
			string str = "";
			huff.fill_list(str);
			Assert::IsTrue(huff.list.isEmpty());
		}
		TEST_METHOD(fill_list_one_elem)
		{
			Huffman huff;
			string str = "i";
			huff.fill_list(str);
			Assert::IsTrue(!huff.list.isEmpty() && huff.list.at(0)->symbol == 'i'
			&& huff.list.at(0)->freq == 1);
		}
		TEST_METHOD(fill_list_two_equal_elems)
		{
			Huffman huff;
			string str = "ii";
			huff.fill_list(str);
			Assert::IsTrue(huff.list.get_size() == 1 && huff.list.at(0)->symbol == 'i'
			&& huff.list.at(0)->freq == 2);
		}
		TEST_METHOD(fill_list_two_different_elems)
		{
			Huffman huff;
			string str = "ia";
			huff.fill_list(str);
			Assert::IsTrue(huff.list.get_size() == 2 && huff.list.at(0)->symbol == 'a'
				&& huff.list.at(1)->symbol == 'i');
		}
		TEST_METHOD(fill_list_three_and_more_elems)
		{
			Huffman huff;
			string str = "is this";
			huff.fill_list(str);
			Assert::IsTrue(huff.list.get_size() == 5 && huff.list.at(0)->symbol == ' '
			&& huff.list.at(3)->symbol == 's' && huff.list.at(3)->freq == 2);
		}





		TEST_METHOD(buildTree_empty)
		{
			Huffman huff;
			string str = "";
			huff.buildTree(str);
			Assert::IsTrue(huff.root == nullptr);
		}
		TEST_METHOD(buildTree_one_elem)
		{
			Huffman huff;
			string str = "i";
			huff.buildTree(str);
			Assert::IsTrue(huff.root->symbol == '\0' && huff.root->left->symbol == 'i');
		}
		TEST_METHOD(buildTree_two_equal_elems)
		{
			Huffman huff;
			string str = "ii";
			huff.buildTree(str);
			Assert::IsTrue(huff.root->symbol == '\0' && huff.root->left->symbol == 'i');
		}
		TEST_METHOD(buildTree_two_different_elems)
		{
			Huffman huff;
			string str = "ia";
			huff.buildTree(str);
			Assert::IsTrue(huff.root->symbol == '\0' && huff.root->right->symbol == 'i'
				&& huff.root->left->symbol == 'a');
		}
		TEST_METHOD(buildTree_three_and_more_elems)
		{
			Huffman huff;
			string str = "ithi";
			huff.buildTree(str);
			Assert::IsTrue(huff.root->symbol == '\0' && huff.root->left->symbol == 'i'
				&& huff.root->right->right->symbol == 't' && huff.root->right->left->symbol == 'h');
		}





		TEST_METHOD(encode_empty)
		{
			Huffman huff;
			string str = "";
			Assert::IsTrue(huff.root == nullptr);
		}

		TEST_METHOD(encode_one_elem)
		{
			Huffman huff;
			string str = "i";
			huff.encode_string(str);
			Assert::IsTrue(huff.root->left->symbol == 'i' && huff.root->left->code == "0");
		}
		TEST_METHOD(encode_two_equals_elems)
		{
			Huffman huff;
			string str = "ii";
			huff.encode_string(str);
			Assert::IsTrue(huff.root->left->symbol == 'i' && huff.root->left->code == "0");
		}
		TEST_METHOD(encode_two_different_elems)
		{
			Huffman huff;
			string str = "ia";
			huff.encode_string(str);
			Assert::IsTrue(huff.root->left->symbol == 'a' && huff.root->left->code == "0"
							&& huff.root->right->symbol == 'i' && huff.root->right->code == "1");
		}
		TEST_METHOD(encode_three_and_more_elems)
		{
			Huffman huff;
			string str = "ithi";
			huff.encode_string(str);
			Assert::IsTrue(huff.root->left->symbol == 'i' && huff.root->left->code == "0" 
				&& huff.root->right->right->symbol == 't' && huff.root->right->right->code == "11"
				&& huff.root->right->left->symbol == 'h' && huff.root->right->left->code == "10");
		}





		TEST_METHOD(decode_empty)
		{
			Huffman huff;
			string str = "";
			huff.encode_string(str);
			try {
				huff.decode_string("1010001001");
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Root is nullptr", error.what());
			}
		}
		TEST_METHOD(decode_one_elem)
		{
			Huffman huff;
			string str = "i";
			huff.encode_string(str);
			string to_decode = huff.decode_string("10010");
			Assert::IsTrue(to_decode == "iii");
		}
		TEST_METHOD(decode_two_equal_elems)
		{
			Huffman huff;
			string str = "ii";
			huff.encode_string(str);
			string to_decode = huff.decode_string("10010");
			Assert::IsTrue(to_decode == "iii");
		}
		TEST_METHOD(decode_two_different_elems)
		{
			Huffman huff;
			string str = "ia";
			huff.encode_string(str);
			string to_decode = huff.decode_string("10010");
			Assert::IsTrue(to_decode == "iaaia");
		}
		TEST_METHOD(decode_three_and_more_elems)
		{
			Huffman huff;
			string str = "ithi";
			huff.encode_string(str);
			string to_decode = huff.decode_string("01110");
			Assert::IsTrue(to_decode == "ith");
		}
	};
}