/* Author:  Taylor Peoples
 * UFID:    1136-2951
 * File:    olsm.h
 */

#ifndef _OLSM_
#define _OLSM_

#include <iostream>

using namespace std;

template <class T>
struct Node {
    Node<T>* next;
    Node<T>* down;
    int row, col;
    T value;

    Node() {};
    Node(int row, int col, const T& value);
    ~Node();
};

template <class T>
class olsm;
template <class T>
ostream& operator<<(ostream&, const olsm<T>&);
template <class T>
istream& operator>>(istream&, const olsm<T>&);

template <class T>
class olsm {
    friend ostream& operator<< <> (ostream&, const olsm<T>&);
    friend istream& operator>> <> (istream&, const olsm<T>&);

    // Properties
    private:
        int numNodes, numRows, numCols;
        Node<T>* header;
    public:
        // Constructor, copy constructor, destructor
        olsm(int numRows = 0, int numCols = 0);
        olsm(const olsm<T>& original);
        ~olsm();

        // Methods
        void setNumRows(int numRows);
        void setNumCols(int numCols);
        int getNumNodes();
        void set(int row, int col, const T& value);
        void insert(int row, int col, const T& value);
        void add(olsm<T>& olsm2);
        void transpose();
        void printSingleRow(int rowNum);
        void printSingleCol(int colNum);
};

#include "olsm.cpp"
#endif
