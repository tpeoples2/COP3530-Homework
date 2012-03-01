/* @author  Taylor Peoples
 * @UFID    1136-2951
 * @date    2012-03-01
 * @HW      HW3 Part A
 *
 */

// chain node

#ifndef chainNode_
#define chainNode_

template <class T>
struct chainNode {
   // data members
   T element;
   chainNode<T> *next;

   // methods
   chainNode() {}
   chainNode(const T& element)
      {this->element = element;}
   chainNode(const T& element, chainNode<T>* next)
      {this->element = element;
       this->next = next;}
};

#endif
