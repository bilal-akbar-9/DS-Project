#include "./graph.h"

int main(){
Graph g;
readData(g);
   bool flag = true;
   while(flag) {
      int choice;
       cout << "\n1.Person with biggest social circle\n2.Social distance between profiles";
       cout << "\n3.Common Profiles\n4.Display\n5.Exit" << endl;
       cin >> choice;
          switch(choice) {
              case 1:{
                 cout << g.biggestSocialCircle();
              }break;
              case 2:{
                 int a, b;
                   cout << "\nEnter ID 1:";
                   cin >> a;
                   cout << "\nEnter ID 2:";
                   cin >> b;
                 g.socialDistancebtw(a, b);
              }break;
              case 3:{
                int a, b;
                   cout << "\nEnter ID 1:";
                   cin >> a;
                   cout << "\nEnter ID 2:";
                   cin >> b;
                g.displayCommonProfiles(a, b);
              }break;
              case 4:{
                g.printStudentsNotInSocialCircle();
              }break;
              case 5:{
                flag = false;
              }break;
              default: {
                cout << "\nInvalid input";
              }break;
          }
   }
return EXIT_SUCCESS;
}