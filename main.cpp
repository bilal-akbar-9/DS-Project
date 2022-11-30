#include "./linkedList.h"
#include"./BPlusTree.h"
template <class T=int>
void Insertion(BPLusTree<T>& tree, StudentList& list) {
    Student* nodePtr = list.getHead();
    while (nodePtr != NULL) {
        tree.insert(nodePtr->ID);
        nodePtr = nodePtr->Next;
    }
    tree.display(tree.getRoot());
}
int main(){
    StudentList l1;
    BPLusTree<int> tree;
    Insertion(tree, l1);
    return EXIT_SUCCESS;
}