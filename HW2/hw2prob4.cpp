/*
 * @name    Taylor Peoples
 * @UFID    1136-2951
 */

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
        // check if the entry has multiple words
        if (char(inFile.peek()) == ' ') {
            string temp2;
            getline(inFile, temp2);
            temp += temp2;
        }
        // check if the file has reached the end
        if (temp.compare("") == 0) {
            continue;
        }
        dictionaryArrayList.insert(i, temp);
        i++;   
    }
    
    inFile.close();

    sort(dictionaryArrayList.beginRA(), dictionaryArrayList.endRA());

    ofstream outFile("sortedDictionary");
    
    if (!outFile) {
        cerr << "Error creating file 'sortedDictionary'. Exiting" << endl;
        return 1;
    }
    dictionaryArrayList.output(outFile);
    outFile.close();
    
    // testing [] operator
    //cout << dictionaryArrayList[0] << endl; // should print 'a'
    //dictionaryArrayList[0] = "TEST";
    //cout << dictionaryArrayList[0] << endl; // should print 'TEST'

    return 0;
}
