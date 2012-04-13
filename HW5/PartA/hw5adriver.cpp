#include <iostream>
#include "linkedBinaryTree.h"

using namespace std;

int main(void) {
    linkedBinaryTree<int> final_tree, empty, tree1, tree2, tree3, tree4, tree5, tree6, tree7, tree8, tree9, tree10;
    linkedBinaryTree<int> treeA, treeB, treeC, treeD, treeE, treeF, treeG;
    tree1.makeTree(1,empty,empty);
    tree2.makeTree(2,empty,empty);
    tree3.makeTree(3,empty,empty);
    tree4.makeTree(4,empty,empty);
    tree5.makeTree(5,empty,empty);
    tree6.makeTree(6,empty,empty);
    tree7.makeTree(7,empty,empty);
    tree8.makeTree(8,empty,empty);
    tree9.makeTree(9,empty,empty);
    tree10.makeTree(10,empty,empty);
    
    treeA.makeTree(5,tree7,tree8);
    treeB.makeTree(2,tree4,treeA);  // left subtree with root 2
    treeC.makeTree(9,empty,tree10);
    treeD.makeTree(6,empty,treeC);
    treeE.makeTree(3,treeD,empty);  // right subtree with root 3

    final_tree.makeTree(1,treeB,treeE);

    cout << "Number of nodes = ";
    cout << final_tree.size() << endl;
    cout << "height = ";
    cout << final_tree.height() << endl;
    cout << "Preorder sequence is ";
    final_tree.preOrderOutput();
    cout << "Inorder sequence is ";
    final_tree.inOrderOutput();
    cout << "Postorder sequence is ";
    final_tree.postOrderOutput();
    cout << "Level order sequence is ";
    final_tree.levelOrderOutput();

    cout << "-----------------------------------" << endl;

    final_tree.verticalSum();
}
