#pragma once
#include "..//Alg_sem4_l2/Map.h"
#include "..//Alg_sem4_l2/Map.cpp"
#include "fstream"

class Graph {
	class Vertex
	{
		//friend Graph;
		string city{}; //verte's name
		size_t edge{}; //lenght of edge from this vertex to adjacent vertex
		size_t weight = 999999999; //vertex's weight
		LinkedList<Vertex*> adjacent{}; //Adjacent vertexes

	public:
		string get_city() { return city; };
		void set_city(string city) { this->city = city; };

		size_t get_edge() { return edge; };
		void set_edge(size_t edge_value) { this->edge = edge_value; };

		size_t get_weight() { return weight; };
		void set_weight(size_t weight) { this->weight = weight; };

		LinkedList<Vertex*>* get_adjacent() { return &adjacent; };

		Vertex(string city)
		{
			this->city = city;
		}
		~Vertex()
		{
			adjacent.clear();
		}
	};

	Map<string, size_t> cities; //map filling with cities and their numbers
	LinkedList<Vertex*> vertexes; //list with main vertexes

	void fill_map();
	void push_vertex(string city, LinkedList<Vertex*> *vertexes); //add the vertex to the vertexe's list
	void initialize_edge(string city1, string city2, size_t edge); //initialize edge from vertex to adjacent vertex
	bool check_vertex(string city, LinkedList<Vertex*> *vertexes); //Check for an vertex existence in the vertex's list
	Vertex *get_vertex(string city) { //return vertex from main vertex's list
		auto *current = vertexes.get_head();
		while (current)
		{
			if (current->data->get_city() == city)
				return current->data;
			current = current->next;
		}
		return nullptr;
	}

public:
	Graph() {};
	~Graph() { vertexes.clear(); cities.clear(); };
	void print_graph();
	void read_file(ifstream &inputFile); //read file and create graph
	void Dijkstra_Algorithm(size_t i, size_t j); //To run Dijkstra's Algorithm
};