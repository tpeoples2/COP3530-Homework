/* Name:    Taylor Peoples
 * UFID:    1136-2951
 * File:    hw5.h
 * Assign:  HW #5
 */

#ifndef _UNDIRECTEDGRAPH_
#define _UNDIRECTEDGRAPH_

#include <iostream>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

class undirectedGraph;
ostream& operator<<(ostream& out, undirectedGraph& graph);
istream& operator>>(istream& in, undirectedGraph& graph);

class undirectedGraph {
    friend ostream& operator<< (ostream& out, undirectedGraph& graph);
    friend istream& operator>> (istream& in, undirectedGraph& graph);
    
    private:
        int numberOfVertices;
        int numberOfEdges;
        vector<list<int> > adjacencyList;
        
        void addVertex(int vertex);
        bool edgeExists(int vertex1, int vertex2);
        void addEdge(int vertex1, int vertex2);
        void utilityFindCycle(int vertex, int previous, vector<bool>& visited, bool& cycle);

    public:
        undirectedGraph();
        undirectedGraph(const undirectedGraph& graph);
        ~undirectedGraph();

        int getNumberOfVertices() const {
            return numberOfVertices;
        }
        int getNumberOfEdges() const {
            return numberOfEdges;
        }
        bool findCycle();
};

undirectedGraph::undirectedGraph() {
    adjacencyList.push_back(list<int>());
    numberOfEdges = 0;
    numberOfVertices = 0;
}
undirectedGraph::undirectedGraph(const undirectedGraph& graph) {
    // ...
}
undirectedGraph::~undirectedGraph() {
    // ...
}

void undirectedGraph::addVertex(int vertex) {
    if (vertex <= numberOfVertices) {
        return;
    }

    while (adjacencyList.size() <= vertex) {
        numberOfVertices++;
        adjacencyList.push_back(list<int>());
    }
}

bool undirectedGraph::edgeExists(int vertex1, int vertex2) {
    for (list<int>::iterator it = adjacencyList[vertex1].begin(); it != adjacencyList[vertex1].end(); it++) {
        if (*it == vertex2) {
            return true;
        }
    }

    return false;
}

void undirectedGraph::addEdge(int vertex1, int vertex2) {
    addVertex(vertex1);
    addVertex(vertex2);

    if (edgeExists(vertex1, vertex2)) {
        return;
    }
    
    adjacencyList[vertex1].push_back(vertex2);
    adjacencyList[vertex2].push_back(vertex1);

    numberOfEdges++;
}

bool undirectedGraph::findCycle() {
    bool cycle = false;

    vector<bool> visited(numberOfVertices + 1);

    for (int i = 1; i < visited.size(); i++) {
        if (visited[i] != true) {
            utilityFindCycle(i, 0, visited, cycle);
        }
    }

    return cycle;
}

void undirectedGraph::utilityFindCycle(int vertex, int previous, vector<bool>& visited, bool& cycle) {
    visited[vertex] = true;

    for (list<int>::iterator it = adjacencyList[vertex].begin(); it != adjacencyList[vertex].end(); it++) {
        if (visited[*it]) {
            if (*it != previous) {
                cycle = true;
            }
        }
        else {
            utilityFindCycle(*it, vertex, visited, cycle);
        }
    }
}

ostream& operator<<(ostream& out, undirectedGraph& graph) {
    out << "Number of Vertices: " << graph.getNumberOfVertices() << endl;
    out << "Number of Edges: " << graph.getNumberOfEdges() << endl;
   
    for (int i = 1; i < graph.adjacencyList.size(); i++) {
        out << "Neighbors of Vertex #" << i << ":";
        for (list<int>::iterator it = graph.adjacencyList[i].begin(); it != graph.adjacencyList[i].end(); it++) {
            out << " " << *it;
        }
        out << endl;
    }

    return out;
}

istream& operator>>(istream& in, undirectedGraph& graph) {
    int numVertices, numEdges;
    in >> numVertices;
    in >> numEdges;
    int vertex1, vertex2;
    for (int i = 0; i < numEdges; i++) {
        in >> vertex1;
        in >> vertex2;
        graph.addEdge(vertex1, vertex2);
    }
    return in;
}

#endif
