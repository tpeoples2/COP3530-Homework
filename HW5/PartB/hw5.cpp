/* Name:    Taylor Peoples
 * UFID:    1136-2951
 * File:    hw5.cpp
 * Assign:  HW5
 */

#include "hw5.h"

int main() {
    undirectedGraph graph;

    ifstream inputFile("test_file");
    if (!inputFile) {
        cerr << "Error opening 'test_file'. Exiting." << endl;
        return 1;
    }
    inputFile >> graph;
    inputFile.close();

    cout << graph;
}
