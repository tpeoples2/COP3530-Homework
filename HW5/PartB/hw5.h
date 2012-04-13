/* Name:    Taylor Peoples
 * UFID:    1136-2951
 * File:    hw5.h
 * Assign:  HW #5
 */

#ifndef _UNDIRECTEDGRAPH_
#define _UNDIRECTEDGRAPH_

#include <iostream>
#include <list>
#include <utility>
#include <fstream>

using namespace std;

class undirectedGraph;
ostream& operator<<(ostream& out, const undirectedGraph& graph);
istream& operator>>(istream& in, undirectedGraph& graph);

class undirectedGraph {
    //friend ostream& operator<< <> (ostream& out, const undirectedGraph& graph);
    //friend istream& operator>> <> (istream& in, undirectedGraph& graph);
    
    private:
        list<int> vertices;
        list<list<int> > adjacencyList;
        int numberOfEdges;
        
        void addVertex(int vertex);
        list<int> getAdjacentNodes(int vertex1);
        bool vertexExists(int vertex);
        bool edgeExists(int vertex1, int vertex2);

    public:
        undirectedGraph();
        undirectedGraph(const undirectedGraph& graph);
        ~undirectedGraph();

        int getNumberOfVertices() {
            return vertices.size();
        }
        int getNumberOfEdges() {
            return numberOfEdges;
        }
        bool findCycle();
        bool depthFirstSearch(int vertex1);
        void addEdge(int vertex1, int vertex2);
        void debugPrint();

};

undirectedGraph::undirectedGraph() {
    adjacencyList.push_back(list<int>());
    numberOfEdges = 0;
}
undirectedGraph::undirectedGraph(const undirectedGraph& graph) {
    // ...
}
undirectedGraph::~undirectedGraph() {
    // ...
}

bool undirectedGraph::vertexExists(int vertex) {
    for (list<int>::iterator it = vertices.begin(); it != vertices.end(); it++) {
        if (vertex == *it) {
            return true;
        }
    }
    return false;
}

void undirectedGraph::addVertex(int vertex) {
    vertices.push_back(vertex);
    while (adjacencyList.size() <= vertex) {
        adjacencyList.push_back(list<int>());
    }
}

void undirectedGraph::addEdge(int vertex1, int vertex2) {
    if (!vertexExists(vertex1)) {
        addVertex(vertex1);
    }
    if (!vertexExists(vertex2)) {
        addVertex(vertex2);
    }
    
    int index = 0;
    for (list<list<int> >::iterator it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        if (index == vertex1) {
            (*it).push_back(vertex2);
            break;
        }
        index++;
    }
    index = 0;
    for (list<list<int> >::iterator it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        if (index == vertex2) {
            (*it).push_back(vertex1);
            break;
        }
        index++;
    }
    numberOfEdges++;
}

bool undirectedGraph::depthFirstSearch(int vertex) {

}

list<int> undirectedGraph::getAdjacentNodes(int vertex) {

}

bool undirectedGraph::findCycle() {
    return true;
}

void undirectedGraph::debugPrint() {
    cout << "Number of Vertices: " << this->getNumberOfVertices() << endl;
    cout << "Number of Edges: " << this->getNumberOfEdges() << endl;
    int index = 1;
    for (list<list<int> >::iterator it = ++adjacencyList.begin(); it != adjacencyList.end(); it++) {
        cout << "Neighbors of Vertex #" << index << ":";
        for (list<int>::iterator neighbor_it = (*it).begin(); neighbor_it != (*it).end(); neighbor_it++) {
            cout << " " << *neighbor_it;
        }
        cout << endl;
        index++;
    }
}

ostream& operator<<(ostream& out, const undirectedGraph& graph) {
    //out << olsm.header->numRows << endl;
    //out << olsm.header->numCols << endl;
    //out << olsm.header->numNodes << endl;
    //Node<T>* currentNode = olsm.header->next;
    //while (currentNode->row != -1) {
        //out << currentNode->row << " " << currentNode->col << " " << currentNode->value << endl;
        //currentNode = currentNode->next;
    //}
    //return out;
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
