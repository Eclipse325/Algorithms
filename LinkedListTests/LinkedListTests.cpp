#include "stdafx.h"
#include "CppUnitTest.h"
#include "..//Alg_sem4_l1/LinkedList.h"
#include "..//Alg_sem4_l1/LinkedList.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTests
{		
	TEST_CLASS(LinkedListTests)
	{
	public:
		
		TEST_METHOD(is_size_Node_empty) //Check for the return of the empty list size
		{
			LinkedList<int> lst;
			Assert::IsTrue(lst.get_size() == 0);
		}


		TEST_METHOD(List_is_Empty) //Check the emptiness of the list (at the beginning the list is always empty)
		{
			LinkedList<int> lst;
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(is_clear_Node_empty) //Check to clear the empty list
		{
			LinkedList<int> lst;
			lst.clear();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(is_clear_Node) //Check to clear the list
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.push_back(4);
			lst.push_back(3);
			lst.clear();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(is_at_Node) //Check taking a list item value
		{
			LinkedList<int> lst;
			lst.push_front(5);
			Assert::IsTrue(lst.at(0) == 5);
		}

		TEST_METHOD(is_add_back_Node) //Check for adding item to the end
		{
			LinkedList<int> lst;
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			Assert::IsTrue(lst.at(2) == 6);
		}

		TEST_METHOD(is_add_front_Node) //Check for adding item to the beginning
		{
			LinkedList<int> lst;
			lst.push_front(4);
			lst.push_front(5);
			lst.push_front(6);
			Assert::IsTrue(lst.at(0) == 6);
		}

		TEST_METHOD(is_insert_Node_empty) //Check to insert an item in an empty list
		{
			LinkedList<int> lst;
			lst.insert(5, 1);
			Assert::IsTrue(lst.at(0) == 1);
		}

		TEST_METHOD(is_insert_Node_one) //Check to insert an item by index into the list with one element
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.insert(0, 6);
			Assert::IsTrue(lst.at(0) == 6);
		}

		TEST_METHOD(is_insert_Node_over) //Check for insertion of an item into the list with an index outside the list
										//(index is reduced to the maximum index of the list)
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.insert(2, 6);
			Assert::IsTrue(lst.at(0) == 6);
		}

		TEST_METHOD(is_insert_Node) //Check to insert an element into the list by index
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.push_back(4);
			lst.insert(6, 1);
			Assert::IsTrue(lst.at(2) == 4);
		}

		TEST_METHOD(is_pop_front_Node_empty) //Check to remove the first item of the empty list
		{
			LinkedList<int> lst;
			lst.pop_front();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(is_pop_front_Node_one) //Check to remove the first item of the list with one element
		{
			LinkedList<int> lst;
			lst.push_front(5);
			lst.pop_front();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(is_pop_front_Node) //Check to remove the first item of the list
		{
			LinkedList<int> lst;
			lst.push_front(5);
			lst.push_front(4);
			lst.push_front(3);
			lst.pop_front();
			Assert::IsTrue((lst.at(0) == 4) && (lst.at(1) == 5) && (lst.get_size() == 2));
		}

		TEST_METHOD(is_pop_back_Node_null) //Check to remove the last item of the empty list
		{
			LinkedList<int> lst;
			lst.pop_back();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(is_pop_back_Node_one) //Check to remove the last item in the list with one item
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.pop_back();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(is_pop_back_Node) //Check to remove the last element of the empty list
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.push_back(4);
			lst.push_back(3);
			lst.pop_back();
			Assert::IsTrue((lst.at(0) == 5) && (lst.at(1) == 4) && (lst.get_size() == 2));
		}

		TEST_METHOD(is_set_Node_null) //Check for replacement of an empty list item
		{
			LinkedList<int> lst;
			//char error;
			try {
				lst.set(0, 5);;
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is greater than list size", error.what());
			}
		}


		TEST_METHOD(is_set_Node) //Check for correct replacement of the item value
		{
			LinkedList<int> lst;
			lst.push_front(5);
			lst.set(0, 1);
			Assert::IsTrue(lst.at(0) == 1);
		}

		TEST_METHOD(is_delete_Node) //Check for deletion of element 
		{
			LinkedList<int> lst;
			lst.push_front(5);
			lst.push_front(6);
			lst.remove(1);
			Assert::IsTrue(lst.at(0) == 6 && lst.get_size() == 1);
		}

		TEST_METHOD(is_swap_Node) //Check the correctness of the exchange of two values by index 
		{
			LinkedList<int> lst;
			lst.push_front(5);
			lst.push_front(6);
			lst.swap(0, 1);
			Assert::IsTrue(lst.at(0) == 5 && lst.at(1) == 6);
		}

		TEST_METHOD(at_exception) //at function exception
		{
			LinkedList<int> lst;
			//char error;
			lst.push_front(5);
			lst.push_front(6);
			try {
				lst.at(5);
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Индекс больше, чем наибольший индекс списка", error.what());
			}
		}

		TEST_METHOD(remove_exception) //remove function exception
		{
			LinkedList<int> lst;
			//char error;
			lst.push_front(5);
			lst.push_front(6);
			try {
				lst.remove(5);
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is greater than list size", error.what());
			}
		}

		TEST_METHOD(set_exception) //Set function exception
		{
			LinkedList<int> lst;
			//char error;
			lst.push_front(5);
			lst.push_front(6);
			try {
				lst.set(5, 13);
			}
			catch (const std::out_of_range &error) {
				Assert::AreEqual("Index is greater than list size", error.what());
			}
		}

	};
}