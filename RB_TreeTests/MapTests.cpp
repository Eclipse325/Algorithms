#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include "..//Alg_sem4_l2/Map.h"
#include "..//Alg_sem4_l2/Map.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RB_TreeTests
{		
	TEST_CLASS(RB_TreeTests)
	{
	public:
		TEST_METHOD(find_empty)
		{
			Map<string, double> tree;
			Assert::IsTrue(tree.find("sas") == nullptr);
		}

		TEST_METHOD(find)
		{
			Map<string, double> tree;
			tree.insert("December", 12);
			tree.insert("January", 1);
			tree.insert("April", 4);
			tree.insert("Jule", 7);
			Assert::IsTrue(tree.find("Jule") != nullptr);
		}

		TEST_METHOD(true_size_empty)
		{
			Map<string, double> tree;
			Assert::IsTrue(tree.size == 0);
		}

		TEST_METHOD(true_size)
		{
			Map<string, double> tree;
			tree.insert("December", 12);
			tree.insert("January", 1);
			tree.insert("April", 4);
			tree.insert("Jule", 7);

			Assert::IsTrue(tree.size == 4);
		}

		TEST_METHOD(remove_empty)
		{
			Map<string, double> tree;
			tree.remove("sas");
			Assert::IsTrue(tree.size == 0 && tree.find("sas") == nullptr);
		}

		TEST_METHOD(remove_one)
		{
			Map<string, double> tree;
			tree.insert("kek", 1);
			tree.remove("kek");
			Assert::IsTrue(tree.size == 0 && tree.find("kek") == nullptr);
		}

		TEST_METHOD(remove_case1_keys) // Remove the red node (CHECK MAIN FILE)
		{
			Map<string, double> tree;
			tree.insert("January", 15);
			tree.insert("February", 6);
			tree.insert("March", 9);
			tree.insert("April", 5); // AFTER THIS INSERTION SOME GOING WRONG
			tree.insert("May", 8);
			tree.insert("June", 15);
			tree.insert("Jule", 1);
			tree.remove("Jule"); //it is red node

			string a1[] = { "January", "February", "April", "March", "June", "May" };
			string *a2 = new string[6];
			auto *iter = tree.create_dft_iterator();
			int i = 0;
			while (iter->has_next()) {
				a2[i] = iter->next()->key;
				i++;
			}
			Assert::IsTrue(tree.are_equal_keys(a1, a2, 6, 6)/*a2[0] == "February" && a2[1] == "April" 
							&& a2[2] == "June" && a2[3] == "January"
							&& a2[4] == "March" && a2[5] == "May"*/ /*tree.root->key == "February"*/); /*MUST BE JANUARY!!!*/
			delete[]a2;
		}

		TEST_METHOD(remove_case1_colors) // Remove the red node 
		{
			Map<string, double> tree;
			tree.insert("January", 15);
			tree.insert("February", 6);
			tree.insert("March", 9);
			tree.insert("April", 5);
			tree.insert("May", 8);
			tree.insert("June", 15);
			tree.insert("Jule", 1);
			tree.remove("Jule"); //it is red node

			bool b1[] = { 1, 1, 0, 0, 1, 1 };
			bool *b2 = new bool[6];
			auto *iter = tree.create_dft_iterator();
			int i = 0;
			while (iter->has_next()) {
				bool kek = iter->next()->color;
				b2[i] = kek;
				i++;
			}
			Assert::IsTrue(tree.are_equal_colors(b1, b2, 6, 6));
			delete[]b2;
		}

		TEST_METHOD(remove_case2)
		{
			Map<string, double> tree;
			tree.insert("January", 15);
			tree.insert("February", 6);
			tree.insert("March", 9);
			tree.insert("April", 5);
			tree.insert("May", 8);
			tree.insert("June", 15);
			tree.insert("Jule", 1);
			tree.insert("Cucumber", 133);
			tree.remove("May");

			string a1[] = { "January", "February", "April", "March", "June", "May" };
			string *a2 = new string[6];
			bool check = true;
			auto *iter = tree.create_dft_iterator();
			//bool check = true;
			int i = 0;
			while (iter->has_next()) {
				string kek = iter->next()->key;
				a2[i] = kek;
				i++;
			}
			check = tree.are_equal_keys(a1, a2, 6, 6);
			Assert::IsTrue(check);
			delete[]a2;
		}

		TEST_METHOD(clear_empty)
		{
			Map<int, double> tree;
			tree.clear();
			Assert::IsTrue(tree.size == 0 && tree.root == nullptr);
		}

		TEST_METHOD(clear_one)
		{
			Map<int, double> tree;
			tree.insert(15, 3.5);
			tree.clear();
			Assert::IsTrue(tree.size == 0 && tree.find(15) == nullptr && tree.root == nullptr);
		}

		TEST_METHOD(clear_two)
		{
			Map<int, double> tree;
			tree.insert(15, 3.5);
			tree.insert(19, 8);
			tree.clear();
			Assert::IsTrue((tree.size == 0) && (!tree.find(15)) && (!tree.find(19)) && (tree.root == nullptr));
		}

		TEST_METHOD(clear_three)
		{
			Map<int, double> tree;
			tree.insert(15, 3.5);
			tree.insert(19, 8);
			tree.insert(10, 1);
			tree.clear();
			Assert::IsTrue(tree.size == 0 && !tree.find(15) && !tree.find(19) && tree.root == nullptr);
		}

		TEST_METHOD(clear)
		{
			Map<int, double> tree;
			tree.insert(1, 12);
			tree.insert(2, 11);
			tree.insert(3, 10);
			tree.insert(4, 9);
			tree.insert(5, 8);
			tree.insert(6, 7);
			tree.insert(7, 6);
			tree.insert(8, 5);
			tree.insert(9, 4);
			tree.insert(10, 3);
			tree.insert(11, 2);
			tree.insert(12, 1);
			tree.clear();
			Assert::IsTrue(tree.size == 0 && tree.root == nullptr);
		}

		TEST_METHOD(getValues_and_getKey_empty)
		{
			Map<string, double> tree;
			Assert::IsTrue(tree.get_keys() && tree.get_values());
		}

		TEST_METHOD(getValues_and_getKey)
		{
			Map<string, double> tree;
			tree.insert("January", 15);
			tree.insert("February", 6);
			tree.insert("March", 9);
			tree.insert("April", 5);
			tree.insert("May", 8);
			tree.insert("June", 15);
			tree.insert("Jule", 1);
			tree.insert("Cucumber", 133);
			Assert::IsTrue(tree.get_keys() && tree.get_values());
		}
	};
}
