/* Name:    Taylor Peoples
 * UFID:    1136-2951
 * Assign:  HW4A
 * File:    linkedBinaryTree.h
 */


// linked binary tree using nodes of type binaryTreeNode
// derives from the abstract class binaryTree

#ifndef linkedBinaryTree_
#define linkedBinaryTree_

using namespace std;

#include <iostream>
#include <map>
#include "binaryTree.h"
#include "arrayQueue.h"
#include "arrayStack.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include "booster.h"


template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> > {
    protected:
        binaryTreeNode<E> *root;                // pointer to root
        int treeSize;                           // number of nodes in tree
        static void (*visit)(binaryTreeNode<E>*);      // visit function
        static int count;         // used to count nodes in a subtree
        static void preOrder(binaryTreeNode<E> *t);
        static void inOrder(binaryTreeNode<E> *t);
        static void postOrder(binaryTreeNode<E> *t);
        static void countNodes(binaryTreeNode<E> *t) {
            visit = addToCount; 
            count = 0;
            preOrder(t);
        }
        static void dispose(binaryTreeNode<E> *t) {
            delete t;
        }
      
        static void addToCount(binaryTreeNode<E> *t) {
            count++;
        }
        static int height(binaryTreeNode<E> *t);
    public:
        linkedBinaryTree() {
            root = NULL; 
            treeSize = 0;
        }
        ~linkedBinaryTree(){
            erase();
        } 
        bool empty() const {
            return treeSize == 0;
        }
        int size() const {
            return treeSize;
        }
        E* rootElement() const;
        void makeTree(const E& element, linkedBinaryTree<E>&, linkedBinaryTree<E>&);
        linkedBinaryTree<E>& removeLeftSubtree();
        linkedBinaryTree<E>& removeRightSubtree();
        void verticalSum();
        void verticalSum(binaryTreeNode<E>* currentNode, int deviation, map<int, E>* map);

        void preOrder(void(*theVisit)(binaryTreeNode<E>*)) {
            visit = theVisit; preOrder(root);
        }
        void inOrder(void(*theVisit)(binaryTreeNode<E>*)) {
            visit = theVisit; 
            inOrder(root);
        }
        void postOrder(void(*theVisit)(binaryTreeNode<E>*)) {
            visit = theVisit; 
            postOrder(root);
        }
        void levelOrder(void(*)(binaryTreeNode<E> *));
        void preOrderOutput() {
            preOrder(output); 
            cout << endl;
        }
        void inOrderOutput() {
            inOrder(output); 
            cout << endl;
        }
        void postOrderOutput() {
            postOrder(output); 
            cout << endl;
        }
        void levelOrderOutput() {
            levelOrder(output); 
            cout << endl;
        }
        void erase() {
            postOrder(dispose);
            root = NULL;
            treeSize = 0;
        }
        int height() const {
            return height(root);
        }
        static void output(binaryTreeNode<E> *t) {
            cout << t->element << ' ';
        }
                  
        class inorderIterator {
            public:
                inorderIterator(binaryTreeNode<E>*);
                bool hasNext();
	            binaryTreeNode<E>* next();
            private:
                arrayStack<binaryTreeNode<E>*> nodeStack;
                binaryTreeNode<E>* currentNode;
        };

        inorderIterator beginIO() {
            return inorderIterator(root);
        }

        class postOrderIterator {
            public:
                postOrderIterator(binaryTreeNode<E>*);
	            bool hasNext();
	            binaryTreeNode<E>* next();
            private:
                arrayStack<binaryTreeNode<E>*> nodeStack;
                binaryTreeNode<E>* currentNode;
        };

        postOrderIterator beginPO() {
            return postOrderIterator(root);
        }
};

// the following should work but gives an internal compiler error
template <class E> void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);
// so the explicit declarations that follow are used for our purpose instead
//void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
//void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
//void (*linkedBinaryTree<pair<int,int> >::visit)(binaryTreeNode<pair<int,int> >*);
//void (*linkedBinaryTree<pair<const int,char> >::visit)(binaryTreeNode<pair<const int,char> >*);
//void (*linkedBinaryTree<pair<const int,int> >::visit)(binaryTreeNode<pair<const int,int> >*);

template<class E>
E* linkedBinaryTree<E>::rootElement() const {
    // Return NULL if no root. Otherwise, return pointer to root element.
    if (treeSize == 0)
        return NULL;  // no root
    else
        return &root->element;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,
           linkedBinaryTree<E>& left, linkedBinaryTree<E>& right) {
    // Combine left, right, and element to make new tree.
    // left, right, and this must be different trees.
    // create combined tree
    root = new binaryTreeNode<E> (element, left.root, right.root);
    treeSize = left.treeSize + right.treeSize + 1;

    // deny access from trees left and right
    left.root = right.root = NULL;
    left.treeSize = right.treeSize = 0;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree() {
    // Remove and return the left subtree.
    // check if empty
    if (treeSize == 0)
        throw emptyTree();

    // detach left subtree and save in leftSubtree
    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = root->leftChild;
    count = 0;
    leftSubtree.treeSize = countNodes(leftSubtree.root);
    root->leftChild = NULL;
    treeSize -= leftSubtree.treeSize;
  
    return leftSubtree;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree() {
    // Remove and return the right subtree.
    // check if empty
    if (treeSize == 0)
        throw emptyTree();

    // detach right subtree and save in rightSubtree
    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = root->rightChild;
    count = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root);
    root->rightChild = NULL;
    treeSize -= rightSubtree.treeSize;
  
    return rightSubtree;
}

template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t) {
    // Preorder traversal.
    if (t != NULL) {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t) {
    // Inorder traversal.
    if (t != NULL) {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t) {
    // Postorder traversal.
    if (t != NULL) {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E> *)) {
    // Level-order traversal.
    arrayQueue<binaryTreeNode<E>*> q;
    binaryTreeNode<E> *t = root;
    while (t != NULL) {
        theVisit(t);  // visit t

        // put t's children on queue
        if (t->leftChild != NULL)
            q.push(t->leftChild);
        if (t->rightChild != NULL)
            q.push(t->rightChild);

        // get next node to visit
        try {
            t = q.front();
        }
        catch (queueEmpty) {
            return;
        }
        q.pop();
   }
}

template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t) {
    // Return height of tree rooted at *t.
    if (t == NULL)
        return 0;                    // empty tree
    int hl = height(t->leftChild);  // height of left
    int hr = height(t->rightChild); // height of right
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}

template <class E>
linkedBinaryTree<E>::inorderIterator::inorderIterator(binaryTreeNode<E>* root) {
    currentNode = root;
    while (currentNode) {
        nodeStack.push(currentNode);
        currentNode = currentNode->leftChild;
    }
}

template <class E>
bool linkedBinaryTree<E>::inorderIterator::hasNext() {
    return !nodeStack.empty() || currentNode->rightChild;
}

template <class E>
binaryTreeNode<E>* linkedBinaryTree<E>::inorderIterator::next() {
    if (currentNode != NULL && currentNode->rightChild) {
        currentNode = currentNode->rightChild;
        while (currentNode->leftChild) {
            nodeStack.push(currentNode);
            currentNode = currentNode->leftChild;
        }
    }
    else {
        currentNode = nodeStack.top();
        nodeStack.pop();
    }
    return currentNode;
}

template <class E>
linkedBinaryTree<E>::postOrderIterator::postOrderIterator(binaryTreeNode<E>* root) {
    currentNode = root;
    while (currentNode) {
        nodeStack.push(currentNode);
        if (currentNode->leftChild) {
            currentNode = currentNode->leftChild;
        }
        else {
            currentNode = currentNode->rightChild;
        }
    }
}

template <class E>
bool linkedBinaryTree<E>::postOrderIterator::hasNext() {
    return !nodeStack.empty();
}

template <class E>
binaryTreeNode<E>* linkedBinaryTree<E>::postOrderIterator::next() {
    if (currentNode == nodeStack.top()->leftChild && nodeStack.top()->rightChild) {
         currentNode = nodeStack.top()->rightChild;
         while (currentNode->leftChild || currentNode->rightChild) {
            nodeStack.push(currentNode);
            if (currentNode->leftChild) {
                currentNode = currentNode->leftChild;
            }
            else {
                currentNode = currentNode->rightChild;
            }
         }
    }
    else {
        currentNode = nodeStack.top();
        nodeStack.pop();
    }
    return currentNode;
}

template <class E>
void linkedBinaryTree<E>::verticalSum() {
    map<int, E> verticalSumMap;
    verticalSum(root, 0, &verticalSumMap);
    cout << "Number of vertical sum columns: " << verticalSumMap.size() << endl;
    for (typename std::map<int, E>::iterator ii = verticalSumMap.begin(); ii != verticalSumMap.end(); ii++) {
        cout << (*ii).first << ": " << (*ii).second << endl;
    }
}

template <class E>
void linkedBinaryTree<E>::verticalSum(binaryTreeNode<E>* currentNode, int deviation, map<int, E>* map) {
    if (currentNode == NULL) { 
        return; 
    }
    verticalSum(currentNode->leftChild, deviation - 1, map);
    
    int oldSum;
    if (!(*map)[deviation]) { 
        oldSum = 0; 
    }
    else { 
        oldSum = (*map)[deviation]; 
    }
    //map.put(deviation, oldSum + currentNode->element);
    (*map)[deviation] = oldSum + currentNode->element;
    
    verticalSum(currentNode->rightChild, deviation + 1, map);
}

#endif
