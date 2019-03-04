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
		
		TEST_METHOD(get_empty_list_size_int) //Check for the return of the empty list size
		{
			LinkedList<int> lst;
			Assert::IsTrue(lst.get_size() == 0);
		}

		TEST_METHOD(get_list_size_int) //Check for the return of list size
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.push_back(4);
			lst.push_back(3);
			Assert::IsTrue(lst.get_size() == 3);
		}

		TEST_METHOD(List_is_Empty_int) //Check the emptiness of the list (at the beginning the list is always empty)
		{
			LinkedList<int> lst;
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(List_is_not_Empty_int)
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.push_back(4);
			lst.push_back(3);
			Assert::IsFalse(lst.isEmpty());
		}

		TEST_METHOD(clear_empty_list_int) //Check to clear the empty list
		{
			LinkedList<int> lst;
			lst.clear();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(clear_list_int) //Check to clear the list
		{
			LinkedList<int> lst;
			lst.push_back(5);
			lst.push_back(4);
			lst.push_back(3);
			lst.clear();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(at_list_item_int) //Check taking a list item value
		{
			LinkedList<int> lst;
			lst.push_front(5);
			Assert::IsTrue(lst.at(0) == 5);
		}

		TEST_METHOD(at_over_int) //at out of range
		{
			LinkedList<int> lst;
			lst.push_front(5);
			lst.push_front(6);
			try {
				lst.at(5);
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

		TEST_METHOD(at_less_int) //at out of range
		{
			LinkedList<int> lst;
			lst.push_front(5);
			lst.push_front(6);
			try {
				lst.at(-1);
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

		TEST_METHOD(push_back_empty_list_char) //Check for adding item to the end of the empty list
		{
			LinkedList<char> lst;
			lst.push_back('a');
			Assert::IsTrue(lst.at(0) == 'a');
		}

		TEST_METHOD(push_back_char) //Check for adding item to the end
		{
			LinkedList<char> lst;
			lst.push_back('a');
			lst.push_back('b');
			lst.push_back('c');
			Assert::IsTrue(lst.at(2) == 'c');
		}

		TEST_METHOD(push_front_empty_list_char) //Check for adding item to the beginning of the empty list
		{
			LinkedList<char> lst;
			lst.push_front('a');
			Assert::IsTrue(lst.at(0) == 'a');
		}

		TEST_METHOD(push_front_char) //Check for adding item to the beginning
		{
			LinkedList<char> lst;
			lst.push_front('a');
			lst.push_front('b');
			lst.push_front('c');
			Assert::IsTrue(lst.at(0) == 'c');
		}

		TEST_METHOD(insert_item_empty_list_double) //Check to insert an item in an empty list
		{
			LinkedList<double> lst;
			try {
				lst.insert(5, 1.125);
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

		TEST_METHOD(insert_item_first_double) //Check to insert an item by index into the beginning
		{
			LinkedList<double> lst;
			lst.push_back(5.5);
			lst.insert(0, 6.6);
			Assert::IsTrue(lst.at(0) == 6.6);
		}

		TEST_METHOD(insert_item_last_double) //Check to insert an item by index into the end
		{
			LinkedList<double> lst;
			lst.push_back(5.5);
			lst.push_back(5.6);
			lst.push_back(5.7);
			lst.insert(2, 6.8);
			Assert::IsTrue(lst.at(2) == 6.8);
		}

		TEST_METHOD(insert_double) //Check to insert an element into the list by index
		{
			LinkedList<double> lst;
			lst.push_back(5.5);
			lst.push_back(4.5);
			lst.push_back(5.7);
			lst.push_back(4.5);
			lst.push_back(5.1);
			lst.push_back(4.3);
			lst.insert(3, 1.3);
			Assert::IsTrue(lst.at(3) == 1.3);
		}

		TEST_METHOD(is_insert_over_double) //Check for insertion of an item into the list with an index outside the list
										//(index is reduced to the maximum index of the list)
		{
			LinkedList<double> lst;
			lst.push_back(5.5);
			lst.push_back(5.5);
			lst.push_back(5.5);
			try {
				lst.set(0, 5);;
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

		TEST_METHOD(is_insert_less_double) //Check for insertion of an item into the list with an index outside the list
										//(index is reduced to the maximum index of the list)
		{
			LinkedList<double> lst;
			lst.push_back(5.5);
			lst.push_back(5.5);
			lst.push_back(5.5);
			try {
				lst.set(0, -1);;
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

		TEST_METHOD(pop_front_empty_list_char) //Check to remove the first item of the empty list
		{
			LinkedList<char> lst;
			lst.pop_front();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(pop_front_char) //Check to remove the first item
		{
			LinkedList<char> lst;
			lst.push_front('c');
			lst.push_front('b');
			lst.push_front('a');
			lst.pop_front();
			Assert::IsTrue((lst.at(0) == 'b') && (lst.at(1) == 'c') && (lst.get_size() == 2));
		}

		TEST_METHOD(pop_back_empty_list_char) //Check to remove the last item of the empty list
		{
			LinkedList<char> lst;
			lst.pop_back();
			Assert::IsTrue(lst.isEmpty());
		}

		TEST_METHOD(pop_back_char) //Check to remove the last element
		{
			LinkedList<char> lst;
			lst.push_back('c');
			lst.push_back('b');
			lst.push_back('a');
			lst.pop_back();
			Assert::IsTrue((lst.at(0) == 'c') && (lst.at(1) == 'b') && (lst.get_size() == 2));
		}

		TEST_METHOD(set_over_of_range_int) //Check for replacement of an empty/over list item
		{
			LinkedList<int> lst;
			try {
				lst.set(0, 5);;
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

		TEST_METHOD(set_less_of_range_int) //Check for replacement of an empty/over list item
		{
			LinkedList<int> lst;
			try {
				lst.set(0, -1);;
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

		TEST_METHOD(set_Node_char) //Check for correct replacement of the item value
		{
			LinkedList<char> lst;
			lst.push_front('a');
			lst.set(0, 'c');
			Assert::IsTrue(lst.at(0) == 'c');
		}

		TEST_METHOD(remove_double) //Check for deletion of element 
		{
			LinkedList<double> lst;
			lst.push_front(5.5);
			lst.push_front(6.6);
			lst.remove(1);
			Assert::IsTrue(lst.at(0) == 6.6 && lst.get_size() == 1);
		}

		TEST_METHOD(remove_over_int) //Check for deletion of element out of range 
		{
			LinkedList<int> lst;
			try {
				lst.remove(1);
			}
			catch(const std::out_of_range& error){
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

		TEST_METHOD(remove_less_int) //Check for deletion of element out of range 
		{
			LinkedList<int> lst;
			try {
				lst.remove(1);
			}
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Index is out of range", error.what());
			}
		}

	};
}
