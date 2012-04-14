/* Name:    Taylor Peoples
 * UFID:    1136-2951
 * File:    hw5.h
 * Assign:  HW #5
 */

#ifndef _UNDIRECTEDGRAPH_
#define _UNDIRECTEDGRAPH_

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class undirectedGraph;
ostream& operator<<(ostream& out, undirectedGraph& graph);
istream& operator>>(istream& in, undirectedGraph& graph);

class undirectedGraph {
    friend ostream& operator<< (ostream& out, undirectedGraph& graph);
    friend istream& operator>> (istream& in, undirectedGraph& graph);
    
    private:
        vector<int> vertices;
        vector<vector<int> > adjacencyList;
        int numberOfEdges;
        
        void addVertex(int vertex);
        bool vertexExists(int vertex);
        bool edgeExists(int vertex1, int vertex2);
        void addEdge(int vertex1, int vertex2);

    public:
        undirectedGraph();
        undirectedGraph(const undirectedGraph& graph);
        ~undirectedGraph();

        int getNumberOfVertices() const {
            return vertices.size();
        }
        int getNumberOfEdges() const {
            return numberOfEdges;
        }
        bool findCycle();
        bool depthFirstSearch(int vertex1);
        ostream& print(ostream& out);

};

undirectedGraph::undirectedGraph() {
    adjacencyList.push_back(vector<int>());
    numberOfEdges = 0;
}
undirectedGraph::undirectedGraph(const undirectedGraph& graph) {
    // ...
}
undirectedGraph::~undirectedGraph() {
    // ...
}

bool undirectedGraph::vertexExists(int vertex) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == vertex) {
            return true;
        }
    }
    return false;
}

void undirectedGraph::addVertex(int vertex) {
    vertices.push_back(vertex);
    while (adjacencyList.size() <= vertex) {
        adjacencyList.push_back(vector<int>());
    }
}

bool undirectedGraph::edgeExists(int vertex1, int vertex2) {
    vector<int> neighbors_of_vertex1 = adjacencyList[vertex1];

    for (int i = 0; i < neighbors_of_vertex1.size(); i++) {
        if (neighbors_of_vertex1[i] == vertex2) {
            return true;
        }
    }

    return false;
}

void undirectedGraph::addEdge(int vertex1, int vertex2) {
    if (!vertexExists(vertex1)) {
        addVertex(vertex1);
    }
    if (!vertexExists(vertex2)) {
        addVertex(vertex2);
    }
    if (edgeExists(vertex1, vertex2)) {
        return;
    }
    
    adjacencyList[vertex1].push_back(vertex2);
    adjacencyList[vertex2].push_back(vertex1);

    numberOfEdges++;
}

bool undirectedGraph::depthFirstSearch(int vertex) {
    //vector<boolean
}

bool undirectedGraph::findCycle() {
    return true;
}

ostream& undirectedGraph::print(ostream& out) {
    out << "Number of Vertices: " << this->getNumberOfVertices() << endl;
    out << "Number of Edges: " << this->getNumberOfEdges() << endl;
   
    for (int i = 1; i < adjacencyList.size(); i++) {
        out << "Neighbors of Vertex #" << i << ":";
        vector<int> temp_neighbors = adjacencyList[i];
        for (int j = 0; j < temp_neighbors.size(); j++) {
            out << " " << temp_neighbors[j];
        }
        out << endl;
    }

    return out;
}

ostream& operator<<(ostream& out, undirectedGraph& graph) {
    return graph.print(out);
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
