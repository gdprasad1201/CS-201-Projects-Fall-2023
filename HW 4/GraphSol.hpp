#ifndef _GRAPHSOL_HPP_
#define _GRAPHSOL_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <limits>
#include <queue>

using namespace std;

#define INFINITY 2147483647

class Vertex {
public:
	bool visited;
	int distance;
	int previous;
	int finish;
	list<int> adj;
};

class Graph {
public:
	Graph(int V, int E, pair<int, int> *edges) {
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
		for (int i=0; i<_V; ++i) {
		    auto adj = vertices[i].adj;
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
		// your implementation goes here
		for (int i = 0; i < _V; i++) {
			vertices[i].visited = false;
			vertices[i].distance = INFINITY;
			vertices[i].previous = -1;
		}
		vertices[s].visited = true;
		vertices[s].distance = 0;
		vertices[s].previous = -1;
		queue<int> Q;
		Q.push(s);
		while(!Q.empty()){
			int u = Q.front();
			Q.pop();
			for(int v : vertices[u].adj){
				if(!vertices[v].visited){
                    vertices[v].visited = true;
                    vertices[v].distance = vertices[u].distance + 1;
                    vertices[v].previous = u;
					Q.push(v);
				}
			}
			vertices[u].visited = true;
		}
	}

	void dfs() {
		// your implementation goes here
		for (int i = 0; i < _V; i++) {
			vertices[i].visited = false;
			vertices[i].previous = -1;
		}
		time = 0;
		for (int i = 0; i < _V; i++) {
			if(!vertices[i].visited){
				dfs_visit(i);
			}
		}
	}

    /* print after visiting */
	void dfs_visit(int u) {
		// your implementation goes here
		time = time + 1;
		vertices[u].distance = time;
		vertices[u].visited = true;
		for(int v : vertices[u].adj){
			if(!vertices[v].visited){
				vertices[v].previous = u;
				dfs_visit(v);
			}
		}
		time = time + 1;
        vertices[u].finish = time;
		cout << u << " ";
	}

    // /* print before visiting */
	// void dfs_visit(int u) {
	// 	// your implementation goes here
	// 	time = time + 1;
	// 	vertices[u].distance = time;
	// 	vertices[u].visited = true;
	// 	cout << u << " ";
	// 	for(int v : vertices[u].adj){
	// 		if(!vertices[v].visited){
	// 			vertices[v].previous = u;
	// 			dfs_visit(v);
	// 		}
	// 	}
	// 	time = time + 1;
    //     vertices[u].finish = time;
	// }

	void print_path(int s, int v) {
		if (v == s)
		   cout << s;
		else if (vertices[v].previous == -1)
		   cout << "not connected";
		else {
		   print_path(s,vertices[v].previous);
		   cout << "->" << v;
		}
	}

	string toString() {
		stringbuf buffer;
		ostream os(&buffer);
		os << "Vertices = " << _V << ", Edges = " << _E << endl;
		for (int i = 0; i < _V; ++i) {
		    os << i << "(" << degree(i) << "): ";
		    for (const auto& l : vertices[i].adj) 
			os << l << " ";
		    os << endl;
		}

		return buffer.str();
	}
private:
	int _V; // no. of vertices
	int _E; // no. of edges
	Vertex *vertices; // array of vertices
	int time;
};

#endif
