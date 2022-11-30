#include "./linkedList.h"
#include"./BPlusTree.h"
template <class T>
void Insertion(BPLusTree<T>& tree, StudentList& list) {
    Student* nodePtr = list.getHead();
    while (nodePtr != NULL) {
        tree.insert(nodePtr->ID);
        nodePtr = nodePtr->Next;
    }
    PointToLinkedList(tree, list);
    tree.displayThroughLeaf(tree.getRoot(), 100, 200);
}
int main(){
    StudentList l1;
    BPLusTree<int> tree;
    Insertion(tree, l1);
    return EXIT_SUCCESS;
}