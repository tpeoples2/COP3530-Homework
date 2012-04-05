// test linked binary tree class

#include <iostream>
#include "linkedBinaryTree.h"

using namespace std;

int main(void)
{
   linkedBinaryTree<int> a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
   linkedBinaryTree<int> tree1, tree2, tree3, tree4, tree5, tree6, tree7, tree8;
   b.makeTree(1,a,a);
   c.makeTree(2,a,a);
   d.makeTree(3,a,a);
   e.makeTree(4,a,a);
   f.makeTree(5,a,a);
   g.makeTree(6,a,a);
   h.makeTree(7,a,a);
   i.makeTree(8,a,a);
   j.makeTree(9,a,a);
   k.makeTree(10,a,a);
   l.makeTree(11,a,a);
   m.makeTree(12,a,a);
   n.makeTree(13,a,a);
   o.makeTree(14,a,a);
   p.makeTree(15,a,a);


    tree1.makeTree(10,a,m);
    tree2.makeTree(5,tree1,a);
    tree3.makeTree(4,a,l);
    tree4.makeTree(2,tree3,tree2);  // left subtree with root 2
    tree5.makeTree(8,j,a);
    tree6.makeTree(7,a,tree5);
    tree7.makeTree(3,g,tree6);      // right subtree with root 3
    tree8.makeTree(1,tree4, tree7);


   cout << "Number of nodes = ";
   cout << tree8.size() << endl;
   cout << "height = ";
   cout << tree8.height() << endl;
   cout << "Preorder sequence is ";
   tree8.preOrderOutput();
   cout << "Inorder sequence is ";
   tree8.inOrderOutput();
   cout << "Postorder sequence is ";
   tree8.postOrderOutput();
   cout << "Level order sequence is ";
   tree8.levelOrderOutput();
   
   
   /////////////////// test for iterators
      
   //POSTORDER ITERATOR
   cout << "---postorder iterator sequence is ";
   linkedBinaryTree<int>::postOrderIterator ip = tree8.beginPO() ;
   while(ip.hasNext())
     tree8.output(ip.next());
   cout << endl;
   
    //INORDER ITERATOR
    cout << "---inorder iterator sequence is ";
    linkedBinaryTree<int>::inorderIterator ioIterator = tree8.beginIO();
    while (ioIterator.hasNext()) {
        tree8.output(ioIterator.next());
    }
    cout << endl;

   return 0;
}
