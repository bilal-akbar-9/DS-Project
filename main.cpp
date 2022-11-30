#include "./linkedList.h"

int main(){
    StudentList l1;
    // l1.addStudent(0, "Tauseef", "02-11-2001", "1-1-2007", "Chakwal", "FSc", 'M');
    readData(l1);
    l1.displayList();
 return EXIT_SUCCESS;
}