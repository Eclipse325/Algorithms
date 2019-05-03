#include "stdafx.h"
#include "CppUnitTest.h"
#include "..//Alg_sem4_l4/Dijkstra.h"
#include "..//Alg_sem4_l4/Dijkstra.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Dijkstra_Tests
{		
	TEST_CLASS(Dijkstra_Tests)
	{
	public:
		
		TEST_METHOD(push_vertex_null) //push vertex into an empty list
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			Assert::IsTrue(graph.vertexes.get_size() != 0 && graph.vertexes.get_head()->data->get_city() == "Александрия");
		}
		TEST_METHOD(push_vertex) //push vertex into a list
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			graph.push_vertex("Рига", &graph.vertexes);
			graph.push_vertex("Медина", &graph.vertexes);
			Assert::IsTrue(graph.vertexes.get_size() != 0 && graph.vertexes.get_head()->data->get_city() == "Александрия"
				&& graph.vertexes.at(1)->get_city() == "Рига" && graph.vertexes.at(2)->get_city() == "Медина");
		}
		TEST_METHOD(push_same_vertex)
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			graph.push_vertex("Александрия", &graph.vertexes);
			Assert::IsTrue(graph.vertexes.get_head()->data->get_city() == "Александрия" 
							&& graph.vertexes.get_size() == 1);
		}


		TEST_METHOD(check_vertex_empty)
		{
			Graph graph;
			Assert::IsTrue(graph.check_vertex("Александрия", &graph.vertexes) == false);
		}
		TEST_METHOD(check_vertex_one)
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			Assert::IsTrue(graph.check_vertex("Александрия", &graph.vertexes) == true);
		}
		TEST_METHOD(check_vertex_not_this)
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			Assert::IsTrue(graph.check_vertex("Мемфис", &graph.vertexes) == false);
		}


		TEST_METHOD(fill_map_empty) //fill map, but "vertexes" is empty
		{
			Graph graph;
			graph.fill_map();
			Assert::IsTrue(graph.cities.get_keys()->get_size() == 0);
		}
		TEST_METHOD(fill_map)
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			graph.push_vertex("Рига", &graph.vertexes);
			graph.push_vertex("Медина", &graph.vertexes);
			graph.fill_map();
			Assert::IsTrue(graph.cities.get_keys()->get_size() == 3);
		}
		TEST_METHOD(fill_map_same_vertexes)
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			graph.push_vertex("Александрия", &graph.vertexes);
			graph.fill_map();
			Assert::IsTrue(graph.cities.get_keys()->get_size() == 1 
							&& graph.cities.get_keys()->get_head()->data == "Александрия");
		}


		TEST_METHOD(get_vertex_empty)
		{
			Graph graph;
			Assert::IsTrue(graph.get_vertex("Стамбул") == nullptr);
		}
		TEST_METHOD(get_vertex)
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			graph.push_vertex("Рига", &graph.vertexes);
			graph.push_vertex("Медина", &graph.vertexes);
			Assert::IsTrue(graph.get_vertex("Рига"));
		}
		TEST_METHOD(get_vertex_nonexistent)
		{
			Graph graph;
			graph.push_vertex("Александрия", &graph.vertexes);
			graph.push_vertex("Рига", &graph.vertexes);
			graph.push_vertex("Медина", &graph.vertexes);
			Assert::IsTrue(!graph.get_vertex("Стамбул"));
		}


		TEST_METHOD(init_edge_empty)
		{
			Graph graph;
			try { graph.initialize_edge("Библ", "Малакка", 10); }
			catch (const std::exception& error) {
				Assert::AreEqual("Doesn't exists", error.what());
			}
		}
		TEST_METHOD(init_edge_not_this_city) //Try lead the edge to nonexistent vertex
		{
			Graph graph;
			graph.push_vertex("Библ", &graph.vertexes);
			graph.push_vertex("Константинополь", graph.vertexes.get_head()->data->get_adjacent());
			try { graph.initialize_edge("Библ", "Малакка", 10); }
			catch (const std::exception& error) {
				Assert::AreEqual("Doesn't exists", error.what());
			}
		}
		TEST_METHOD(init_edge) //Try lead the edge to nonexistent vertex
		{
			Graph graph;
			graph.push_vertex("Библ", &graph.vertexes);
			graph.push_vertex("Малакка", graph.vertexes.get_head()->data->get_adjacent());
			graph.initialize_edge("Библ", "Малакка", 10);
			Assert::IsTrue(graph.get_vertex("Библ")->get_adjacent()->get_head()->data->get_edge() == 10);
		}


		TEST_METHOD(Dijkstra_Algorithm_exception) //Try lead the edge to nonexistent vertex
		{
			Graph graph;
			try { graph.Dijkstra_Algorithm(-1, 2); }
			catch (const std::out_of_range& error) {
				Assert::AreEqual("Out of range", error.what());
			}
		}
	};
}