#include <fstream>
#include "olsm.h"

template <class T>
ostream& operator<<(ostream& out, const olsm<T>& olsm) {
    out << olsm.header->numRows << endl;
    out << olsm.header->numCols << endl;
    out << olsm.header->numNodes << endl;
    Node<T>* currentNode = olsm.header->next;
    while (currentNode->row != -1) {
        out << currentNode->row << " " << currentNode->col << " " << currentNode->value << endl;
        currentNode = currentNode->next;
    }
    return out;
}

template <class T>
istream& operator>>(istream& in, olsm<T>& olsm) {
    int numRows, numCols, numNodes;
    in >> numRows;
    in >> numCols;
    in >> numNodes;
    olsm.setNumRows(numRows);
    olsm.setNumCols(numCols);
    int rowNum, colNum;
    T value;
    for (int i = 0; i < numNodes; i++) {
        in >> rowNum;
        in >> colNum;
        in >> value;
        olsm.insert(rowNum, colNum, value);
    }
    return in;
}

int main() {
    olsm<int> olsmA;
    ifstream inputFile1("hw3bin1");
    
    if (!inputFile1) {
        cerr << "Error opening 'hw3bin1'. Exiting." << endl;
        return 1;
    }

    inputFile1 >> olsmA;
    //cout << olsmA;

    olsm<int> transposeOfA;
    transposeOfA.transpose(olsmA);

    olsm<int> olsmB;
    ifstream inputFile2("hw3bin2");

    if (!inputFile2) {
        cerr << "Error opening 'hw3bin2'. Exiting." << endl;
        return 1;
    }

    inputFile2 >> olsmB;
    //cout << olsmB;

    olsm<int> finalOLSM;
    finalOLSM.add(transposeOfA, olsmB);
    //cout << finalOLSM;
    
    ofstream outputFile("hw3bout");

    if (!outputFile) {
        cerr << "Error opening 'hw3bout'. Printing the output instead then exiting." << endl;
        cout << finalOLSM << endl;
        return 1;
    }
    
    outputFile << finalOLSM;

    //olsm<int> olsm4;
    //olsm4.transpose(olsm1);
    //cout << olsm4;

    //olsm<double> olsmDouble1;
    //ifstream doubleFile1("double_test1");

    //if (!doubleFile1) {
        //cerr << "Error opening 'double_test1'. Exiting." << endl;
        //return 1;
    //}

    //doubleFile1 >> olsmDouble1;
    //cout << olsmDouble1;

    //olsm<double> olsmDouble2;
    //ifstream doubleFile2("double_test2");

    //if (!doubleFile2) {
        //cerr << "Error opening 'double_test2'. Exiting." << endl;
        //return 1;
    //}

    //doubleFile2 >> olsmDouble2;
    //cout << olsmDouble2;

    //olsm<double> addedDouble;
    //addedDouble.add(olsmDouble1, olsmDouble2);
    //cout << addedDouble;
    
    //addedDouble.add(olsmDouble1, olsmDouble1);
    //cout << addedDouble;

    //addedDouble.transpose(addedDouble);
    //cout << addedDouble;

    //olsm<string> olsmString1;
    //ifstream stringFile1("string_test1");

    //if (!stringFile1) {
        //cerr << "Error opening 'string_test1'. Exiting." << endl;
        //return 1;
    //}

    //stringFile1 >> olsmString1;
    //cout << olsmString1;

    //olsm<string> olsmString2;
    //ifstream stringFile2("string_test2");

    //if (!stringFile2) {
        //cerr << "Error opening 'string_test2'. Exiting." << endl;
        //return 1;
    //}

    //stringFile2 >> olsmString2;
    //cout << olsmString2;

    //olsm<string> addedString;
    //addedString.add(olsmString1, olsmString2);
    //cout << addedString;

    //olsm<string> transposeString;
    //transposeString.transpose(olsmString2);
    //cout << transposeString;

    //test.insert(1, 2, 5);
    //test.insert(1, 3, 9);
    //test.insert(2, 1, 1);
    //test.insert(3, 1, 1);
    //test.insert(3, 2, 7);

    //test.printSingleRow(1);
    //test.printSingleRow(2);
    //test.printSingleRow(3);
    //test.printSingleRow(4);
    //test.printSingleRow(5);

    //test.printSingleCol(1);
    //test.printSingleCol(2);
    //test.printSingleCol(3);
    //test.printSingleCol(4);

    //cout << "\n\nSize:\t" << test.getNumNodes() << endl;

    //test.~olsm();
}
