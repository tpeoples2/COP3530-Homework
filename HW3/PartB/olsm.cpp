/* Author:  Taylor Peoples
 * UFID:    1136-2951
 * File:    olsm.cpp
 */

template <class T>
Node<T>::Node(int row, int col, const T& value) {
    this->row = row;
    this->col = col;
    this->value = value;
    this->next = this;
    this->down = this;
}

template <class T>
Node<T>::~Node() {
    // ...
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
    // TODO: fix the memory deallocation issues
    //Node<T>* tempNode;
    //Node<T>* currentNode = header->next;
    //while (currentNode->row != -1) {
        //tempNode = currentNode->next;
        //delete currentNode;
        //currentNode = tempNode;
    //}
    //delete currentNode;
}

template <class T>
int olsm<T>::getNumNodes() {
    return this->numNodes;
}

template <class T>
void olsm<T>::setNumRows(int numRows) {
    this->numRows = numRows;
}

template <class T>
void olsm<T>::setNumCols(int numCols) {
    this->numCols = numCols;
}

template <class T>
void olsm<T>::set(int row, int col, const T& value) {
    // TODO: implement
}

template <class T>
void olsm<T>::insert(int row, int col, const T& value) {
    if (value == 0) {
        // no point in storing a value of 0 in a sparse matrix
        return;
    }
    Node<T>* insertNode = new Node<T>(row, col, value);
    
    bool done = false;

    if (header->down->col == -1) {
        // this is the first node being inserted
        insertNode->down = header;
        header->down = insertNode;
        insertNode->next = header;
        header->next = insertNode;
        done = true;
    }
    if (insertNode->col <= header->down->col) {
        if (insertNode->row < header->down->row || insertNode->col < header->down->col) {
            // this is the farthest left node being inserted
            insertNode->down = header->down;
            header->down = insertNode;
            if (insertNode->row <= header->next->row) {
                // this is the closest node to the top left being inserted
                insertNode->next = header->next;
                header->next = insertNode;
            }
            else {
                // need to update the next list
                Node<T>* currentNode = header;
                while (currentNode->next->row < insertNode->row && currentNode->next->row != -1)  {
                    currentNode = currentNode->next;
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
        // this is the highest node being inserted
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
        // the node being inserted altered header->next or header->down and has been taken care of 
        numNodes++;
        return;
    }

    // the node being inserted does not alter the header and therefore find where it fits in both next and down lists
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

    numNodes++;
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
    cout << "\n---PRINTING ROW " << rowNum << endl;
    Node<T>* currentNode = header->next;
    
    while (currentNode->row < rowNum && currentNode->row != -1) {
        currentNode = currentNode->next;
    }

    Node<T>* currentRowNode = currentNode;
    while (currentRowNode->row != -1 && currentRowNode->row == rowNum) {
        cout << "(" << currentRowNode->row << "," << currentRowNode->col << "):\t" << currentRowNode->value << endl;
        currentRowNode = currentRowNode->next;
    }
}

template <class T>
void olsm<T>::printSingleCol(int colNum) {
    cout << "\n---PRINTING COLUMN " << colNum << endl;
    Node<T>* currentNode = header->down;
    
    while (currentNode->col < colNum && currentNode->col != -1) {
        currentNode = currentNode->down;
    }

    Node<T>* currentColNode = currentNode;
    while (currentColNode->col != -1 && currentColNode->col == colNum) {
        cout << "(" << currentColNode->row << "," << currentColNode->col << "):\t" << currentColNode->value << endl;
        currentColNode = currentColNode->down;
    }
}

template <class T>
ostream& operator<<(ostream& out, const olsm<T>& olsm) {
    out << "placeholder" << endl;
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

