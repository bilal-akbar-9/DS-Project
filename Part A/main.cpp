#include "./linkedList.h"
#include"./BPlusTree.h"

void Search(StudentList& list) {
    int choose = 0;
    while (choose != 4) {
        cout << "1.Search by name\n2.Search by ID\n3.Search in Range\n4. Exit\n";
        cin >> choose;
        switch (choose)
        {
        case 1: {
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
            break;
        }
        case 2: {
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
            break;
        }
        case 4:
            break;
        default:
            cout << "Invalid input\n";
            break;
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

void change(StudentList& list) {
    int flag = true;
    while (flag) {
        int choice;
        cout << "\n1. Change by ID\n2. Change by Name\n3. Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1: {

        }break;
        case 2: {
        }break;
        case 3: {
            flag = false;}
              break;
        default:
            cout << "Invalid input\n";
            break;
        }
    }
}
int main() {
    StudentList l1;
    int choose = 0;
    while (choose != 4) {
        cout << "1.Search\n2.Change\n3.Delete\n4.Exit\n";
        cin >> choose;
        switch (choose)
        {
        case 1:
            Search(l1);
            break;
        case 2:
            change(l1);
        case 4:
            break;
        default:
            break;
        }
    }
    BPLusTree<int> tree;
    return EXIT_SUCCESS;
}