#include "pch.h"
#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"
#include <cstdlib>
#include <Windows.h>
using namespace std;

void text()
{
	cout << "Лабораторная работа №1 \"Шаблонный класс списка\"\nКарманов Д. гр.7302 вариант 2\n";
	cout << "\n1. Добавить элемент в конец списка\n";
	cout << "2. Добавить элемент в начало списка\n";
	cout << "3. Удалить последний элемент списка\n";
	cout << "4. Удалить первый элемент списка\n";
	cout << "5. Добавить элемент по индексу\n";
	cout << "6. Получить элемент по индексу\n";
	cout << "7. Удалить элемент по индексу\n";
	cout << "8. Получить размер списка\n";
	cout << "9. Вывести элементы списка\n";
	cout << "10. Удалить все элементы списка\n";
	cout << "11. Замена элемента по индексу на передаваемый элемент\n";
	cout << "12. Проверка списка на пустоту\n";
	cout << "13. Поменять местами два элемента списка\n";

	cout << "\nДополнительные функции:\n-1. Выйти из программы\n-2. Очистить лишний текст\n";
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
		cout << "\nВведите опцию: "; cin >> t;
		switch (t)
		{
		case -2: system("cls"); text(); break;
		case -1: break;
		case 1: cout << "Введите значение элемента: "; cin >> value; lst.push_back(value); break;
		case 2: cout << "Введите значение элемента: "; cin >> value; lst.push_front(value); break;
		case 3: lst.pop_back(); break;
		case 4: lst.pop_front(); break;
		case 5: cout << "Введите значение: "; cin >> value; cout << "Введите индекс: "; cin >> index; lst.insert(index, value); break;
		case 6: cout << "Введите индекс: "; cin >> index; cout << lst.at(index) << endl; break;
		case 7: cout << "Введите индекс: "; cin >> index; lst.remove(index); break;
		case 8: cout << "Размер списка " << lst.get_size() << endl; break;
		case 9: cout << lst; break;
		case 10: lst.clear(); break;
		case 11: cout << "\nВведите значение: "; cin >> value; cout << "Введие индекс: "; cin >> index; lst.set(index, value); break;
		case 12: cout << lst.isEmpty() << endl; break;
		case 13: cout << "\nВведите первый индекс: "; cin >> index; cout << "Введите второй индекс: "; cin >> index1; lst.swap(index, index1); break;
		}
	} while (t != -1);
	system("cls");

	cout << "\nBon Voyage!\n";

	return 0;
}