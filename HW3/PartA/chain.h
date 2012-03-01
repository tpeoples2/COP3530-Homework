/* @author  Taylor Peoples
 * @UFID    1136-2951
 * @date    2012-03-01
 * @HW      HW3 Part A
 *
 */

// linked implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented

#ifndef chain_
#define chain_

#include<iostream>
#include<sstream>
#include<string>
#include "linearList.h"
#include "chainNode.h"
#include "myExceptions.h"

using namespace std;

//class linkedDigraph;
//template <class T> 
//class linkedWDigraph;

template<class T>
class chain : public linearList<T> 
{
   //friend linkedDigraph;
   //friend linkedWDigraph<int>;
   //friend linkedWDigraph<float>;
   //friend linkedWDigraph<double>;
   public:
      // constructor, copy constructor and destructor
      chain(int initialCapacity = 10);
      chain(const chain<T>&);
      ~chain();

      // ADT methods
      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;
      void reverse();
      void meld(chain<T>& a, chain<T>& b);
      void split(chain<T>& a, chain<T>& b);

   protected:
      void checkIndex(int theIndex) const;
            // throw illegalIndex if theIndex invalid
      chainNode<T>* firstNode;  // pointer to first node in chain
      int listSize;             // number of elements in list
};

template<class T>
void chain<T>::split(chain<T>& a, chain<T>& b) {
    // check if the chain being split can even be split
    // if it can't, assign its only node to b
    if (this->listSize <= 1) {
        b.firstNode = this->firstNode;
        b.listSize++;
        this->listSize--;
        this->firstNode = NULL;
        return;
    }
    
    // create a temp node to hold position of chain being split
    chainNode<T>* currentNode = this->firstNode;
    
    // set b's first node to be the start of the split chain's first node
    b.firstNode = currentNode;
    b.listSize++;
    this->listSize--;
    // create a temp node to hold position of b chain
    chainNode<T>* bNode = b.firstNode;
    
    // increment the current node of split chain
    currentNode = currentNode->next;
    
    // set a's first node to be the second node of the split chain
    a.firstNode = currentNode;
    a.listSize++;
    this->listSize--;
    chainNode<T>* aNode = a.firstNode;
    
    // increment the current node of split chain
    currentNode = currentNode->next;
    
    // counter variable to determine which chain to insert into
    int count = 2;
    while (currentNode != NULL) {
        // even indices go to b
        if (count % 2 == 0) {
            bNode->next = currentNode;
            bNode = bNode->next;
            b.listSize++;
        }
        // odd indices go to a
        else {
            aNode->next = currentNode;
            aNode = aNode->next;
            a.listSize++;
        }
        currentNode = currentNode->next;
        this->listSize--;
        count++;
    }
    
    // set the last node of both chains to point to NULL
    aNode->next = NULL;
    bNode->next = NULL;

    // set the firstNode of c to point to NULL
    this->firstNode = NULL;
}

template<class T>
void chain<T>::meld(chain<T>& a, chain<T>& b) {
    // check if either chain is empty
    chainNode<T>* aNode = a.firstNode;
    chainNode<T>* bNode = b.firstNode;
    if (aNode == NULL && bNode == NULL) {
        return; // both chains are empty, nothing to meld
    }
    else if (aNode == NULL && bNode != NULL) {
        this->firstNode = bNode;
        bNode = bNode->next;
        b.listSize--;
        this->listSize++;
    }
    else {
        this->firstNode = aNode;
        aNode = aNode->next;
        a.listSize--;
        this->listSize++;
    }
    
    chainNode<T>* currentNode = this->firstNode;
    int count = 1;
    
    while (aNode != NULL && bNode != NULL) {
        if (count % 2 == 0) {
            currentNode->next = aNode;
            aNode = aNode->next;
            a.listSize--;
        }
        else {
            currentNode->next = bNode;
            bNode = bNode->next;
            b.listSize--;
        }
        currentNode = currentNode->next;
        this->listSize++;
        count++;
    }
    
    // check if one or the other is empty
    // if so, add in the remaining elements
    if (aNode == NULL) {
        while (bNode != NULL) {
            currentNode->next = bNode;
            currentNode = currentNode->next;
            bNode = bNode->next;
            b.listSize--;
            this->listSize++;
        }
    }
    if (bNode == NULL) {
        while (aNode != NULL) {
            currentNode->next = aNode;
            currentNode = currentNode->next;
            aNode = aNode->next;
            a.listSize--;
            this->listSize++;
        }
    }

    a.firstNode = NULL;
    b.firstNode = NULL;
}

/* Complexity is is Theta(n) because you have to manually change every 
 * elements next pointer */
template<class T>
void chain<T>::reverse() {
    chainNode<T>* previousNode = NULL;
    chainNode<T>* currentNode = firstNode;
    chainNode<T>* nextNode = NULL;
    
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        currentNode->next = previousNode;
        previousNode = currentNode;
        currentNode = nextNode;
    }

    firstNode = previousNode;
}

template<class T>
chain<T>::chain(int initialCapacity)
{// Constructor.
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }
   firstNode = NULL;
   listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList)
{// Copy constructor.
   listSize = theList.listSize;

   if (listSize == 0)
   {// theList is empty
      firstNode = NULL;
      return;
   }

   // non-empty list
   chainNode<T>* sourceNode = theList.firstNode;
                    // node in theList to copy from
   firstNode = new chainNode<T>(sourceNode->element);
                    // copy first element of theList
   sourceNode = sourceNode->next;
   chainNode<T>* targetNode = firstNode;
                    // current last node in *this
   while (sourceNode != NULL)
   {// copy remaining elements
      targetNode->next = new chainNode<T>(sourceNode->element);
      targetNode = targetNode->next;
      sourceNode = sourceNode->next;
   }
   targetNode->next = NULL; // end the chain
}

template<class T>
chain<T>::~chain()
{// Chain destructor. Delete all nodes in chain.
   while (firstNode != NULL)
   {// delete firstNode
      chainNode<T>* nextNode = firstNode->next;
      delete firstNode;
      firstNode = nextNode;
   }
}

template<class T>
void chain<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
   if (theIndex < 0 || theIndex >= listSize)
   {ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
   }

}

template<class T>
T& chain<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // move to desired node
   chainNode<T>* currentNode = firstNode;
   for (int i = 0; i < theIndex; i++)
      currentNode = currentNode->next;

   return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search the chain for theElement
   chainNode<T>* currentNode = firstNode;
   int index = 0;  // index of currentNode
   while (currentNode != NULL && 
          currentNode->element != theElement)
   {
      // move to next node
      currentNode = currentNode->next;
      index++;
   }

   // make sure we found matching element
   if (currentNode == NULL)
      return -1;
   else
      return index;
}

template<class T>
void chain<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
   checkIndex(theIndex);

   // valid index, locate node with element to delete
   chainNode<T>* deleteNode;
   if (theIndex == 0)
   {// remove first node from chain
      deleteNode = firstNode;
      firstNode = firstNode->next;
   }
   else 
   {  // use p to get to predecessor of desired node
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; i++)
         p = p->next;
   
      deleteNode = p->next;
      p->next = p->next->next; // remove deleteNode from chain
   }
   listSize--;
   delete deleteNode;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
   if (theIndex < 0 || theIndex > listSize)
   {// invalid index
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw illegalIndex(s.str());
   }

   if (theIndex == 0)
      // insert at front
      firstNode = new chainNode<T>(theElement, firstNode);
   else
   {  // find predecessor of new element
      chainNode<T>* p = firstNode;
      for (int i = 0; i < theIndex - 1; i++)
         p = p->next;
   
      // insert after p
      p->next = new chainNode<T>(theElement, p->next);
   }
   listSize++;
}

template<class T>
void chain<T>::output(ostream& out) const
{// Put the list into the stream out.
   for (chainNode<T>* currentNode = firstNode;
                      currentNode != NULL;
                      currentNode = currentNode->next)
      out << currentNode->element << " ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const chain<T>& x)
   {x.output(out); return out;}

/* WORKING VERSION, NOT OPTIMIZED
 * Runs in O(n^3) time, terrible
 * Try using iterators
 */
template <class T>
chain<T>& reverse(chain<T>& oldChain) {
    if (oldChain.empty())
        return oldChain;

    int size = oldChain.size();

    chain<T> c(size);
    for (int i = 0; i < size; i++) {
        c.insert(i, oldChain.get(size - i - 1));
    }

    for (int i = 0; i < size; i++) {
        oldChain.erase(i);
        oldChain.insert(i, c.get(i));
    }

    return oldChain;
}

#endif
