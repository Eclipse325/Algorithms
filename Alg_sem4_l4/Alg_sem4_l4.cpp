#include "pch.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Dijkstra.h"
using namespace std;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Karmanov Dmitry, gr.7302. Dijkstra's Algorithm.\n";
	Graph graph;
	ifstream file("travels.txt", ios::in);

	if (!file.is_open())
		return 1;

	graph.read_file(file);
	graph.print_graph();
	
	size_t i, j;

	do {
		cout << "Enter the 'i' and 'j': "; cin >> i >> j;
		graph.Dijkstra_Algorithm(i, j);
		cout << "\n\n";
	} while (i != -1);
}
