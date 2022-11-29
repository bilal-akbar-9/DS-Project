#include "./linkedList.h"

int main(){
    StudentList l1;
    l1.addStudent(0, "Tauseef", "02-11-2001", "1-1-2007", "Chakwal", "FSc", 'M');
    l1.addStudent(1, "Irfa", "18-04-2002", "1-2-2008", "Chakwal", "FSc", 'F');
    readData(l1);
    l1.displayList();
 return EXIT_SUCCESS;
}