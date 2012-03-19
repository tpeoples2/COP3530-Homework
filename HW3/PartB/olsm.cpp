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
Header<T>::Header(int numNodes, int numRows, int numCols) {
    this->numNodes = numNodes;
    this->numRows = numRows;
    this->numCols = numCols;
    this->row = -1;
    this->col = -1;
    this->next = this;
    this->down = this;
}

template <class T>
olsm<T>::olsm(int numRows, int numCols) {
    this->header = new Header<T>(0, numRows, numCols);
}

// TODO: implement copy constructorer
template <class T>
olsm<T>::olsm(const olsm<T>& original) {
    this->header->numNodes = original->header->numNodes;
    this->header->numRows = original->header->numRows;
    this->header->numCols = original->header->numCols;
    Node<T>* tempNode = original->header->next;
    while (tempNode->row != -1) {
        this->insert(tempNode->row, tempNode->col, tempNode->value);
    }
}

// TODO: implement destructor
template <class T>
olsm<T>::~olsm() {
    // TODO: fix the memory deallocation issues
    Node<T>* tempNode;
    Node<T>* currentNode = header->next;
    while (currentNode->row != -1) {
        tempNode = currentNode->next;
        delete currentNode;
        currentNode = tempNode;
    }
    delete currentNode;
}

template <class T>
int olsm<T>::getNumNodes() {
    return this->header->numNodes;
}

template <class T>
void olsm<T>::setNumRows(int numRows) {
    this->header->numRows = numRows;
}

template <class T>
void olsm<T>::setNumCols(int numCols) {
    this->header->numCols = numCols;
}

template <class T>
void olsm<T>::set(int row, int col, const T& value) {
    // TODO: implement
}

template <class T>
void olsm<T>::insert(int row, int col, const T& value) {
    //TODO: find a better way to decide if value is empty that works
    // with ints, doubles, and strings
    if (value == 0 ) {
        // no point in storing a value of 0 in a sparse matrix
        return;
    }
    Node<T>* tempNode = this->header->next;
    while (tempNode->row != -1) {
        if (tempNode->row == row && tempNode->col == col) {
            return;     // node already exists
        }
        tempNode = tempNode->next;
    }
    Node<T>* insertNode = new Node<T>(row, col, value);
    
    bool done = false;

    if (header->down->col == -1) {
        // this is the first node being inserted
        //cout << "Inserting first node" << endl;
        insertNode->down = header;
        header->down = insertNode;
        insertNode->next = header;
        header->next = insertNode;
        done = true;
    }
    if (insertNode->col <= header->down->col) {
        if (insertNode->row < header->down->row || insertNode->col < header->down->col) {
            // this is the farthest left node being inserted
            //cout << "Inserting farthest left node" << endl;
            insertNode->down = header->down;
            header->down = insertNode;
            if (insertNode->row <= header->next->row) {
                // this is the closest node to the top left being inserted
                //cout << "Inserting farthest left node" << endl;
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
        //cout << "Inserting highest left node" << endl;
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
        this->header->numNodes++;
        //cout << "header->next: " << header->next->row << " " << header->next->col << " " << header->next->value << endl;
        //cout << "header->down: " << header->down->row << " " << header->down->col << " " << header->down->value << endl;
        //cout << "insert->next: " << insertNode->next->row << " " << insertNode->next->col << " " << insertNode->next->value << endl;
        //cout << "insert->down: " << insertNode->down->row << " " << insertNode->down->col << " " << insertNode->down->value << endl;
        return;
    }

    // the node being inserted does not alter the header and therefore find where it fits in both next and down lists
    //cout << "Inserting in between node" << endl;
    Node<T>* currentNode = header;
    while (currentNode->next->row < insertNode->row && currentNode->next->row != -1) {
        currentNode = currentNode->next;
    }
    while (currentNode->next->col < insertNode->col && currentNode->next->row <= insertNode->row && currentNode->next->col != -1) {
        currentNode = currentNode->next;
    }
    
    //cout << currentNode->next->value << endl;
    insertNode->next = currentNode->next;
    currentNode->next = insertNode;

    currentNode = header;
    while (currentNode->down->col <= insertNode->col && currentNode->down->col != -1) {
        currentNode = currentNode->down;
    }
    
    insertNode->down = currentNode->down;
    currentNode->down = insertNode;

    this->header->numNodes++;

    //cout << "header->next: " << header->next->row << " " << header->next->col << " " << header->next->value << endl;
    //cout << "header->down: " << header->down->row << " " << header->down->col << " " << header->down->value << endl;
    //cout << "insert->next: " << insertNode->next->row << " " << insertNode->next->col << " " << insertNode->next->value << endl;
    //cout << "insert->down: " << insertNode->down->row << " " << insertNode->down->col << " " << insertNode->down->value << endl;
}

template <class T>
void olsm<T>::add(olsm<T>& olsm1, olsm<T>& olsm2) {
    if (olsm1.header->numRows != olsm2.header->numRows || olsm1.header->numCols != olsm2.header->numCols) {
        cerr << "Matrix dimensions do not match. Can not add. Exiting" << endl;
        return;
    }

    // TODO: deal with the call olsm1.transpose(olsm1)
    
    this->header->numRows = olsm1.header->numRows;
    this->header->numCols = olsm2.header->numCols;

    this->clear();

    Node<T>* currentNode1 = olsm1.header;
    Node<T>* currentNode2 = olsm2.header;

    Node<T>* currentNode = this->header;
    while (currentNode1->next->row != -1) {
        while (currentNode2->next->row <= currentNode1->next->row && currentNode2->next->row != -1) { 
            if (currentNode2->next->row == currentNode1->next->row) {
                if (currentNode2->next->col <= currentNode1->next->col) {
                    currentNode2 = currentNode2->next;
                }
                else {
                    break;
                }
            }
            else {
                currentNode2 = currentNode2->next;
            }
        }
        //cout << currentNode1->next->row << currentNode1->next->col;
        //cout << " " << currentNode2->row << currentNode2->col << endl;
        if (currentNode1->next->row == currentNode2->row && currentNode1->next->col == currentNode2->col) {
            this->insert(currentNode1->next->row, currentNode1->next->col, currentNode1->next->value + currentNode2->value);
        }
        else {
            this->insert(currentNode1->next->row, currentNode1->next->col, currentNode1->next->value);
        }
        currentNode1 = currentNode1->next;
    }

    currentNode2 = olsm2.header->next;
    while (currentNode2->row != -1) {
        this->insert(currentNode2->row, currentNode2->col, currentNode2->value);
        currentNode2 = currentNode2->next;
    }
}

template <class T>
void olsm<T>::transpose(olsm<T>& olsm1) {
    this->header->numRows = olsm1.header->numCols;
    this->header->numCols = olsm1.header->numRows;
    Node<T>* currentNode = olsm1.header->next;
    
    // TODO: deal with the call olsm1.transpose(olsm1)

    this->clear();

    while (currentNode->next->row != -1) {
        insert(currentNode->col, currentNode->row, currentNode->value);
        currentNode = currentNode->next;
    }

    insert(currentNode->col, currentNode->row, currentNode->value);
}

template <class T>
void olsm<T>::clear() {
    Node<T>* tempNode;
    Node<T>* currentNode = header->next;
    while (currentNode->row != -1) {
        tempNode = currentNode->next;
        delete currentNode;
        currentNode = tempNode;
    }

    header->next = header;
    header->down = header;
    header->numNodes = 0;
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

    cout << "hmm..." << endl;
}
