/* Author:  Taylor Peoples
 * UFID:    1136-2951
 * File:    olsm.cpp
 */

#include <iostream>

using namespace std;

template <class T>
Node<T>::Node(int row, int col, const T& value) {
    this->row = row;
    this->col = col;
    this->value = value;
    this->next = this;
    this->down = this;
}

template <class T>
olsm<T>::olsm(int numRows, int numCols) {
    this->numRows = numRows;
    this->numCols = numCols;
    this->numNodes = 0;
    this->header = new Node<T>(-1, -1, NULL);
}

// TODO: implement copy constructor
template <class T>
olsm<T>::olsm(const olsm<T>& original) {
    // ...
}

// TODO: implement destructor
template <class T>
olsm<T>::~olsm() {
    // ...
}

template <class T>
void olsm<T>::set(int row, int col, const T& value) {
    // TODO: implement
}

template <class T>
void olsm<T>::insert(int row, int col, const T& value) {
    Node<T>* insertNode = new Node<T>(row, col, value);
    cout << "---------------INSERTING A NEW NODE--------------" << endl;
    cout << "insertNode->row:\t" << insertNode->row << endl;
    cout << "insertNode->col:\t" << insertNode->col << endl;
    cout << "insertNode->value:\t" << insertNode->value << endl;
    
    bool done = false;

    if (header->down->col == -1) {
        cout << "INSERTING FIRST NODE" << endl;
        insertNode->down = header;
        header->down = insertNode;
        insertNode->next = header;
        header->next = insertNode;
        done = true;
    }
    if (insertNode->col <= header->down->col) {
        if (insertNode->row < header->down->row || insertNode->col < header->down->col) {  
            cout << "INSERTING FARTHEST LEFT NODE" << endl;
            insertNode->down = header->down;
            header->down = insertNode;
            if (insertNode->row <= header->next->row) {
                insertNode->next = header->next;
                header->next = insertNode;
            }
            else {
                Node<T>* currentNode = header;
                while (currentNode->next->row < insertNode->row && currentNode->next->row != -1)  {
                    currentNode = currentNode->next;
                    //cout << currentNode->value << endl;
                }
                while (currentNode->next->col < insertNode->col && currentNode->next->col != -1) {
                    currentNode = currentNode->next;
                }
                insertNode->next = currentNode->next;
                currentNode->next = insertNode;
            }
            done = true;
        }
    }
    
    if (insertNode->row < header->next->row) {
        cout << "INSERTING FARTHEST UP NODE" << endl;
        insertNode->next = header->next;
        header->next = insertNode;
    
        Node<T>* currentNode = header;
        while (currentNode->down->col <= insertNode->col && currentNode->down->col != -1) {
            currentNode = currentNode->down;
        }

        insertNode->down = currentNode->down;
        currentNode->down = insertNode;

        done = true;
    }

    if (done) {
        cout << "\nheader->next->row:\t" << header->next->row << endl;
        cout << "header->next->col:\t" << header->next->col << endl;
        cout << "header->down->row:\t" << header->down->row << endl;
        cout << "header->down->col:\t" << header->down->col << endl;
        return;
    }

    cout << "INSERTING NODE SOMEWHERE IN BETWEEN" << endl;
   
    Node<T>* currentNode = header;
    while (currentNode->next->row < insertNode->row && currentNode->next->row != -1) {
        currentNode = currentNode->next;
    }
    while (currentNode->next->col < insertNode->col && currentNode->next->col != -1) {
        currentNode = currentNode->next;
    }

    insertNode->next = currentNode->next;
    currentNode->next = insertNode;

    currentNode = header;
    while (currentNode->down->col <= insertNode->col && currentNode->down->col != -1) {
        currentNode = currentNode->down;
    }
    
    insertNode->down = currentNode->down;
    currentNode->down = insertNode;
   
    cout << "\nheader->next->row:\t" << header->next->row << endl;
    cout << "header->next->col:\t" << header->next->col << endl;
    cout << "header->down->row:\t" << header->down->row << endl;
    cout << "header->down->col:\t" << header->down->col << endl;
}

template <class T>
void olsm<T>::add(olsm<T>& olsm2) {
    // TODO: implement
}

template <class T>
void olsm<T>::transpose() {
    // TODO: implement
}

template <class T>
void olsm<T>::printSingleRow(int rowNum) {
    //cout << "(" << header->next->row << ", " << header->next->col << "): " << header->next->value << endl;
    //cout << "(" << header->down->row << ", " << header->down->col << "): " << header->down->value << endl;
    Node<T>* currentNode = header;
    
    T table[numRows][numCols];
    for (int row = 1; row <= numRows; row++) {
        for (int col = 1; col <= numCols; col++) {
            table[row][col] = 0;
        }
    }

    currentNode = currentNode->down;
    while (currentNode != header) {
        Node<T>* currentRowNode = currentNode;
        while (currentRowNode->row != -1) {
            table[currentRowNode->row][currentRowNode->col] = currentRowNode->value;
            currentRowNode = currentRowNode->next;
        }
        currentNode = currentNode->down;
    }

    for (int i = 1; i <= numRows; i++) {
        if (!table[rowNum][i] == 0) {
            cout << "(" << rowNum << ", " << i << "): " << table[rowNum][i] << endl;
        }
    }
}

template <class T>
void olsm<T>::printSingleCol(int colNum) {
    
}

template <class T>
void olsm<T>::print() {
    // TODO: implement
}
