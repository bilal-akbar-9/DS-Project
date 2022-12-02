#include "./linkedList.h"
#include"./BPlusTree.h"
#include"./search.h"
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