/* Name:    Taylor Peoples
 * UFID:    1136-2951
 * File:    hw5.cpp
 * Assign:  HW5
 */

#include "hw5.h"

int main() {
    undirectedGraph graph;

    ifstream inputFile("hw5part1in.txt");
    if (!inputFile) {
        cerr << "Error opening 'hw5part1in.txt'. Exiting." << endl;
        return 1;
    }
    inputFile >> graph;
    inputFile.close();

    //cout << graph;

    ofstream outputFile("hw5part1out.txt");
    outputFile << "Cycle: ";
    if (graph.findCycle()) {
        outputFile << "Yes" << endl;
    }
    else {
        outputFile << "No" << endl;
    }
}
