#include "pch.h"
#include "Dijkstra.h"


void Graph::print_graph()
{
	try {
		if (vertexes.get_head() == nullptr)
			throw exception("Doesn't exsist");
		auto *current = vertexes.get_head();
		cout << endl;
		while (current != nullptr)
		{
			cout << "№" << cities.find(current->data->get_city())->value << ": " << current->data->get_city() << endl;
			current = current->next;
		}

		current = vertexes.get_head();
		while (current != nullptr)
		{
			auto* current1 = current->data->get_adjacent()->get_head();
			cout << current->data->get_city() << "(" << current->data->get_edge() << ") [" << current->data->get_weight() << "]";;
			while (current1 != nullptr) {
				cout << " -> " << current1->data->get_city() << "(" << current1->data->get_edge() << ") [" << current1->data->get_weight() << "]";
				current1 = current1->next;
			}
			current = current->next;
			cout << endl;
		}
		cout << endl;
	}

	catch (exception)
	{
		return;
	}
}

void Graph::fill_map()
{
	size_t number = 0;
	auto *current = vertexes.get_head();
	while (current != nullptr)
	{
		cities.insert(current->data->get_city(), number);
		number++;
		current = current->next;
	}
}

bool Graph::check_vertex(string city, LinkedList<Vertex*> *vertexes) //There is the vertex in this vertex list?
{
	if (vertexes == nullptr)
		return false;

	auto *current = vertexes->get_head();
	while (current != nullptr) {
		if (current->data->get_city() == city)
			return true;
		current = current->next;
	}

	return false;
}

void Graph::push_vertex(string city, LinkedList<Vertex*> *vertexes) //Push the city into the vertex list
{
	if (!check_vertex(city, vertexes)) {
		Vertex *vertex = new Vertex(city);
		vertexes->push_back(vertex);
	}
}

void Graph::initialize_edge(string city1, string city2, size_t edge) //initialize edge from vertex to adjacent vertex
{
	try {
		if (vertexes.get_head() == nullptr)
			throw exception("Doesn't exists");
		if(!check_vertex(city1, &vertexes))
			throw exception("Doesn't exists");
		auto *current = vertexes.get_head();
		while (current->data->get_city() != city1)
			current = current->next;

		if(!check_vertex(city2, current->data->get_adjacent()))
			throw exception("Doesn't exists");
		auto *current1 = current->data->get_adjacent()->get_head();
		while (current1->data->get_city() != city2)
			current1 = current1->next;

		current1->data->set_edge(edge);
	}

	catch (exception) {
		return;
	}
}

void Graph::read_file(ifstream &inputFile)  //read file and create graph
{
	Graph graph;
	string text;
	string city1;
	string city2;
	string edge1;
	string edge2;
	Vertex *vertex1 = nullptr;
	Vertex *vertex2 = nullptr;
	int e1, e2;
	size_t k = 0; //Counter

	while (!inputFile.eof())
	{
		getline(inputFile, text);
		for (size_t i = 0; i < text.length(); i++)
		{
			if (text[i] != ';' && k == 0)
				city1 += text[i];
			else if (text[i] != ';' && k == 1)
				city2 += text[i];
			else if (text[i] == ';')
				k++;

			if (k == 2)
			{
				push_vertex(city1, &vertexes);
				push_vertex(city2, &vertexes);
				k++;
			}


			if (k == 3 && text[i] != ';')
				edge1 += text[i];

			if (k == 4)
			{
				while (text[i] == ';')
					i++;
				while (i != text.length()) {
					edge2 += text[i];
					i++;
				}

				if (edge1 == "N/A")
					e1 = 0;
				else e1 = stoi(edge1);

				if (edge2 == "N/A")
					e2 = 0;
				else e2 = stoi(edge2);

				vertex1 = get_vertex(city1);
				vertex2 = get_vertex(city2);

				if (e1 != 0) {
					push_vertex(city2, vertex1->get_adjacent());
					initialize_edge(city1, city2, e1);
				}
				if (e2 != 0) {
					push_vertex(city1, vertex2->get_adjacent());
					initialize_edge(city2, city1, e2);
				}

				city1 = city2 = edge1 = edge2 = "";
				k = 0;
			}
		}
	}

	fill_map();

	inputFile.close();
}

void Graph::Dijkstra_Algorithm(size_t i, size_t j)
{
	try {
		if (i < 0 || i >= vertexes.get_size() || j < 0 || j >= vertexes.get_size())
			throw out_of_range("Out of range");
		auto *cur = vertexes.get_head();
		Vertex *vertex1 = nullptr;
		Vertex *vertex2 = nullptr;
		LinkedList<Vertex*> proc_vertexes; //processed vertexes


		while (cur != nullptr)
		{
			if (cities.find(cur->data->get_city())->value == j)
				vertex2 = cur->data;
			if (cities.find(cur->data->get_city())->value == i)
				vertex1 = cur->data;
			cur = cur->next;
		}

		vertex1->set_weight(0); //initialize all i-th vertexes with weight 0, and all the rest are conditional infinity
		cur = vertexes.get_head();
		while (cur) {
			if (cur->data->get_city() == vertex1->get_city())
				cur->data->set_weight(0);
			else cur->data->set_weight(999999999);
			auto *cur1 = cur->data->get_adjacent()->get_head();
			while (cur1 != nullptr) {
				if (cur1->data->get_city() == vertex1->get_city())
					cur1->data->set_weight(0);
				else cur1->data->set_weight(999999999);
				cur1 = cur1->next;
			}
			cur = cur->next;
		}

		//Run Dijkstra algorithm
		while (vertexes.get_head())
		{
			size_t index = 0;
			Vertex *vertex = vertexes.get_head()->data;
			size_t min = vertexes.get_head()->data->get_weight();
			cur = vertexes.get_head();

			while (cur) //searching vertex with minimal weight	 
			{
				if (cur->data->get_weight() < min)
				{
					min = cur->data->get_weight();
					vertex = cur->data;
				}
				cur = cur->next;
			}

			cur = vertexes.get_head(); //take vertex index with minimal weight
			while (cur->data->get_city() != vertex->get_city()) {
				cur = cur->next;
				index++;
			}

			auto *cur1 = cur->data->get_adjacent()->get_head();
			while (cur1 != nullptr)
			{
				if (cur1->data->get_weight() > cur->data->get_weight() + cur1->data->get_edge())
				{
					cur1->data->set_weight(cur->data->get_weight() + cur1->data->get_edge());
					auto *cur3 = vertexes.get_head();
					while (cur3 != nullptr)
					{
						if (cur3->data->get_city() == cur1->data->get_city())
							cur3->data->set_weight(cur->data->get_weight() + cur1->data->get_edge());
						auto *cur4 = cur3->data->get_adjacent()->get_head();
						while (cur4 != nullptr)
						{
							if (cur4->data->get_city() == cur1->data->get_city())
								cur4->data->set_weight(cur->data->get_weight() + cur1->data->get_edge());
							cur4 = cur4->next;
						}
						cur3 = cur3->next;
					}
				}

				cur1 = cur1->next;
			}

			proc_vertexes.push_back(cur->data);
			vertexes.remove(index);
		}

		while (proc_vertexes.get_size() != 0) //Recreate main vertex list
		{
			vertexes.push_front(proc_vertexes.get_head()->data);
			proc_vertexes.remove(0);
		}

		print_graph();

		cur = vertexes.get_head();
		while (cur != nullptr) {
			cout << cur->data->get_city() << " вес " << cur->data->get_weight() << endl;
			cur = cur->next;
		}

		cout << "\nThe most efficient way from the i-vertex " << i << " to j-vertex " << j << " is " << vertex2->get_weight();
	}
	
	catch (out_of_range)
	{
		return;
	}
}