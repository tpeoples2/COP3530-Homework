#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "arrayList.h"

int main() {
    ifstream inFile("Dictionary");
    if (!inFile) {
        cerr << "Error opening 'Dictionary'. Exiting." << endl;
        return 1;
    }
    
    arrayList<string> dictionaryArrayList; 
    
    int i = 0;
    while (inFile) {
        string temp;
        inFile >> temp;
        if (temp.compare("") == 0) {
            continue;
        }
        dictionaryArrayList.insert(i, temp);
        i++;
    }
    
    inFile.close();

    sort(dictionaryArrayList.beginRA(), dictionaryArrayList.endRA());

    ofstream outFile("SortedDictionary");
    
    if (!outFile) {
        cerr << "Error creating file 'SortedDictionary'. Exiting" << endl;
        return 1;
    }
    dictionaryArrayList.output(outFile);
    outFile.close();
    
    // testing [] operator
    cout << dictionaryArrayList[0] << endl; // should print 'a'
    dictionaryArrayList[0] = "TEST";
    cout << dictionaryArrayList[0] << endl; // should print 'TEST'

    return 0;
}
