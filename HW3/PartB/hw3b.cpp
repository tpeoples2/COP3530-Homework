#include "olsm.h"

#include <fstream>

int main() {
    //olsm<int> test(); // this was fun to debug
    olsm<int> olsm1;
    ifstream inputFile1("hw3bin1");
    
    if (!inputFile1) {
        cerr << "Error opening 'hw3bin1'. Exiting." << endl;
        return 1;
    }

    inputFile1 >> olsm1;
    cout << olsm1;

    olsm<int> olsm2;
    ifstream inputFile2("hw3bin2");

    if (!inputFile2) {
        cerr << "Error opening 'hw3bin2'. Exiting." << endl;
        return 1;
    }

    inputFile2 >> olsm2;
    cout << olsm2;

    //olsm<int> test(4, 4);
   
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
