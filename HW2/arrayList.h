#ifndef _ARRAYLIST_
#define _ARRAYLIST_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

using namespace std;

template<class T>
class arrayList : public linearList<T> {
    protected:
        void checkIndex(int theIndex) const;
        T* element;
        int arrayLength;
        int listSize;

    public:
        // constructor, copy constructor, destructor
        arrayList(int initialCapacity = 10);
        arrayList(const arrayList<T>&);
        ~arrayList() {
            delete [] element;
        }

        // ADT methods
        bool empty() const {
            return listSize == 0;
        }
        int size() const {
            return listSize;
        }
        T& get(int theIndex) const;
        int indexOf(const T& theElement) const;
        void erase(int theIndex);
        void insert(int theIndex, const T& theElement);
        void output(ostream& out) const;

        // other methods
        int capacity() const {
            return arrayLength;
        }
        
        void reverse();

        class iterator;
        iterator begin() {
            return iterator(element);
        }
        iterator end() {
            return iterator(element + listSize);
        }

        class seamlessPointer;
        seamlessPointer beginRA() {
            return seamlessPointer(element);
        }
        seamlessPointer endRA() {
            return seamlessPointer(element + listSize);
        }

        T& operator[](int n) const {
            return this->get(n);
        }

        class iterator {
            protected:
                T* position;
            public:
                // typedefs required by C++ for bidirectional iterator
                typedef bidirectional_iterator_tag iterator_category;
                typedef T value_type;
                typedef ptrdiff_t difference_type;
                typedef T* pointer;
                typedef T& reference;

                // constructor
                iterator(T* thePosition = 0) {
                    position = thePosition;
                }
                
                // dereferencing operators
                T& operator*() const {
                    return *position;
                }
                T* operator->() const {
                    return &*position;
                }

                // increment
                iterator& operator++() {
                    ++position;
                    return *this;
                }
                iterator operator++(int) {
                    iterator old = *this;
                    ++position;
                    return old;
                }

                // decrement
                iterator& operator--() {
                    --position;
                    return *this;
                }
                iterator operator-- (int) {
                    iterator old = *this;
                    --position;
                    return old;
                }

                // equality testing
                bool operator!=(const iterator right) const {
                    return position != right.position;
                }

                bool operator==(const iterator right) const {
                    return position == right.position;
                }
        };

        class seamlessPointer : public iterator {
            protected:
                void checkIndex(int theIndex) const;
                T* element;
                int arrayLength;
                int listSize;
            public:
                // typedefs required by C++ for a bidirectional iterator
                typedef random_access_iterator_tag iterator_category;
                typedef T value_type;
                typedef ptrdiff_t difference_type;
                typedef T* pointer;
                typedef T& reference;

                // constructor
                seamlessPointer(T* thePosition = 0) {
                    this->position = thePosition;
                }

                // increment
                seamlessPointer& operator+=(ptrdiff_t n) {
                    iterator::position = iterator::position + n;
                    return *this;
                }
                seamlessPointer operator+(ptrdiff_t n) {
                    return seamlessPointer(iterator::position+n);
                }

                // decrement
                seamlessPointer& operator-=(ptrdiff_t n) {
                    iterator::position = iterator::position - n;
                    return *this;
                }
                seamlessPointer operator-(ptrdiff_t n) {
                    return seamlessPointer(iterator::position-n);
                }

                ptrdiff_t operator-(seamlessPointer ptr) {
                    return iterator::position - ptr.position;
                }
                bool operator<(const seamlessPointer &ptr) const {
                    return iterator::position < ptr.position;    
                }
                bool operator>(const seamlessPointer & ptr) const {
                    return iterator::position > ptr.position;
                }
                bool operator>=(const seamlessPointer & ptr) const {
                    return iterator::position >= ptr.position;
                }
                bool operator<=(const seamlessPointer & ptr) const {
                    return iterator::position <= ptr.position;
                } 
                T& operator[](ptrdiff_t n) const {
                    return this->position[n];
                }
        };
};

template<class T>
arrayList<T>::arrayList(int initialCapacity) {
    if (initialCapacity < 1) {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
T& arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const {
    int theIndex = (int) (find(element, element + listSize, theElement) - element);
    if (theIndex == listSize)
        return -1;
    else
        return theIndex;
}

template<class T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    --listSize;
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    if (listSize == arrayLength) {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;

    listSize++;
}

template<class T>
void arrayList<T>::output(ostream& out) const {
    copy(element, element + listSize, ostream_iterator<T>(out, "\n"));
}

template<class T>
void arrayList<T>::reverse() {
    for (int i = 0; i < listSize/2; i++) {
        swap(element[i], element[listSize - i - 1]);
    }
}

template<class T>
void reverse(arrayList<T>& arr) {
    int listSize = arr.size();
    T temp1, temp2;
    for (int i = 0; i < listSize/2; i++) {
        temp1 = arr.get(i);
        temp2 = arr.get(listSize - i - 1);
        arr.erase(listSize - i - 1);
        arr.erase(i);
        arr.insert(listSize - i - 1, temp1);
        arr.insert(i, temp2);
    }
}

#endif







