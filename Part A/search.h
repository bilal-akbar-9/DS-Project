#pragma once
#include"include.h"
#include"linkedList.h"
#include"BPlusTree.h"
void Search(StudentList& list) {
    int choose = 0;
    while (choose != 4) {
        cout << "1.Search by name\n2.Search by ID\n3.Search by Query\n4. Exit\n";
        cin >> choose;
        if (choose == 1) {
            string name;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            BPLusTree<string> tree;
            Student* nodePtr = list.getHead();
            list.sortListByName();
            while (nodePtr != nullptr) {
                tree.insertString(nodePtr->Name);
                nodePtr = nodePtr->Next;
            }
            PointToLinkedList(tree, list);
            tree.displayParticularString(name);
        }
        else if (choose == 2) {
            int Id;
            cout << "Enter Id: ";
            cin >> Id;
            BPLusTree<int> tree;
            Student* nodePtr = list.getHead();
            list.sortListByID();
            while (nodePtr != nullptr) {
                tree.insert(nodePtr->ID);
                nodePtr = nodePtr->Next;
            }
            PointToLinkedList(tree, list);
            tree.displayParticular(Id);
        }
        else if (choose == 3) {
            string query;
            cout << "Choose a query: \n1.ID\n2.First name\n3.Number of Females\n4.Number of Males\n";
            

        }
        else if (choose == 4) {
            break;
        }
        else {
            cout << "Invalid input\n";
        }
        // BPLusTree<T>& tree;
        // Student* nodePtr = list.getHead();
        // if (typeid(tree.getRoot()) == typeid(int*)) {
        //     while (nodePtr != NULL) {
        //         tree.insert(nodePtr->ID);
        //         nodePtr = nodePtr->Next;
        //     }
        // }
        // else if
        //     PointToLinkedList(tree, list);
    }
}
