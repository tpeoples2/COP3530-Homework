/* Author:  Taylor Peoples
 * UFID:    1136-2951
 * File:    olsm.h
 */

#ifndef _OLSM_
#define _OLSM_

template <class T>
struct Node {
    Node<T>* next;
    Node<T>* down;
    int row, col;
    T value;

    Node() {};
    Node(int row, int col, const T& value);
};


template <class T>
class olsm {
    // Properties
    private:
        int numNodes, numRows, numCols;
        Node<T>* header;
    public:
        // Constructor, copy constructor, destructor
        olsm() {};
        olsm(int numRows = 0, int numCols = 0);
        olsm(const olsm<T>& original);
        ~olsm();

        // Methods
        void set(int row, int col, const T& value);
        void insert(int row, int col, const T& value);
        void add(olsm<T>& olsm2);
        void transpose();
        void printSingleRow(int rowNum);
        void printSingleCol(int colNum);
        void print();
};


#include "olsm.cpp"
#endif
