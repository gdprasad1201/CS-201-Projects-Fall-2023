/*  
   Name: Gowtham Prasad
   Email: gdprasad@crimson.ua.edu
   Course Section: Fall 2023 CS 201  
   Homework #: 4
   To Compile: g++ -std=c++20 GraphDemo.cpp
   To Run: ./a.exe input1.txt
		   ./a.exe input2.txt
*/

#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <queue>
#include <limits>

using namespace std;

#define INFINITY numeric_limits<int>::infinity();

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	list<int> adj;
};

class Graph {
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex* vertices; // array of vertices
	int time = 0; // time for DFS
public:
	Graph(int V, int E, pair<int, int>* edges) {
		_V = V;
		_E = E;
		vertices = new Vertex[_V];
		for (int i = 0; i < _V; i++) {
            vertices[i].visited = false;
            vertices[i].distance = INFINITY;
            vertices[i].previous = -1;
		}
		for (int i = 0; i < _E; i++) {
		    addEdge(edges[i].first, edges[i].second);
		}
	}

	virtual ~Graph() {
		for (int i = 0; i < _V; i++) {
		    list<int> adj = vertices[i].adj;
		    adj.clear(); // clear list
		}
		delete[] vertices; // delete array of vertices
	}

	int V() {
		return _V;
	}

	int E() {
		return _E;
	}

	void addEdge(int u, int v) {
		vertices[u].adj.push_back(v);
	}

	list<int> getEdges(int u) {
		return vertices[u].adj;
	}

	int degree(int u) {
		return vertices[u].adj.size();
	}

	void bfs(int s) {
		for (int u = 0; u < _V; u++) { // initialize vertices for BFS
		    vertices[u].visited = false; 
		    vertices[u].distance = INFINITY;
		    vertices[u].previous = -1;
		}

		vertices[s].visited = true; // initialize source vertex
		vertices[s].distance = 0;  // initialize source vertex
		vertices[s].previous = -1; // initialize source vertex

		queue<int> q; // create queue
		q.push(s); // enqueue source vertex
		
		while(!q.empty()) { // while queue is not empty
		    int u = q.front();
			q.pop(); // dequeue
		    for (const auto& v : vertices[u].adj) { // for each vertex v adjacent to u
				if (!vertices[v].visited) { // if v is not visited 
				    vertices[v].visited = true;
				    vertices[v].distance = vertices[u].distance + 1;
				    vertices[v].previous = u;
				    q.push(v); // enqueue v
				}
		    }
			vertices[u].visited = true; // mark u as visited
		}
	}

	void dfs() {
		for (int u = 0; u < _V; u++) { // initialize vertices for DFS
		    vertices[u].visited = false;
			vertices[u].distance = INFINITY;
		    vertices[u].previous = -1;
		}

		for (int u = 0; u < _V; u++) { // for each vertex u in V do DFS_visit if u is not visited 
		    if (!vertices[u].visited) {
				dfs_visit(u); // DFS_visit(u)
		    }
		}
	}

	void dfs_visit(int u) { // DFS_visit(u)
		time++; // increment time
		vertices[u].distance = time; // set distance of u
		vertices[u].visited = true; // mark u as visited
		for (const auto& v : vertices[u].adj) { // for each vertex v adjacent to u
		    if (!vertices[v].visited) {
				vertices[v].previous = u; // set previous of v to u
				dfs_visit(v); // DFS_visit(v)
		    }
		}
		time++; // increment time
		vertices[u].finish = time; // set finish time of u
		vertices[u].visited = true; // mark u as visited
		cout << "Vertex " << u << " visited, distance = " << vertices[u].distance << "/" << vertices[u].finish << endl; // print vertex u
	}

	void print_path(int s, int v) {
		if (v == s)
		   cout << s;
		else if (vertices[v].previous == -1)
		   cout << "not connected";
		else {
		   print_path(s, vertices[v].previous);
		   cout << "->" << v;
		}
	}

	string toString() {
		stringbuf buffer;
		ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) {
				os << l << " ";
			}
		    os << endl;
		}
		return buffer.str();
	}
};

#endif /* _GRAPH_HPP_ */