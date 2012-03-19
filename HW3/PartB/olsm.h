/* Author:  Taylor Peoples
 * UFID:    1136-2951
 * File:    olsm.h
 */

#ifndef _OLSM_
#define _OLSM_

#include <iostream>

using namespace std;

template <class T>
class Node {
    public:
        Node<T>* next;
        Node<T>* down;
        int row, col;
        T value;

        Node() {};
        Node(int row, int col, const T& value);
        ~Node();
};

template <class T>
class Header : public Node<T> {
    public:
        int numNodes, numRows, numCols;

        Header() {};
        Header(int numNodes, int numRows, int numCols);
        ~Header();
};

template <class T>
class olsm;
template <class T>
ostream& operator<<(ostream& out, const olsm<T>& olsm);
template <class T>
istream& operator>>(istream& in, olsm<T>& olsm);

template <class T>
class olsm {
    friend ostream& operator<< <> (ostream& out, const olsm<T>& olsm);
    friend istream& operator>> <> (istream& in, olsm<T>& olsm);

    // Properties
    private:
        //int numNodes, numRows, numCols;
        //Node<T>* header;
        Header<T>* header;
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
        void add(olsm<T>& olsm1, olsm<T>& olsm2);
        void transpose(olsm<T>& olsm1);
        void clear();
        void printSingleRow(int rowNum);
        void printSingleCol(int colNum);
};

#include "olsm.cpp"
#endif
