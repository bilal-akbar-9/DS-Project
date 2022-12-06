#include "./include.h"
#define MAXVEX 500
//undirected graph implementation using linked list representation of adjacency list

class Node{
  public:
    int data;
    int index;
    int socialCircle;
    Node *next;
    Node (int, int);
};

Node::Node(int a, int b = -1): data(a), index(b), next(NULL){}

class Graph{
  public:
    int V;
    Node ** adjList;
    Graph();
    void addEdge(int, int);
    void addVertexAtRowHead(int, int);
    void addFriend(int, int);
    void printGraph();
    void setIndex();
    int biggestSocialCircle();
    void socialDistancebtw(int, int);
    void displayCommonProfiles(int, int);
    void printStudentsNotInSocialCircle();
    // void ;
    // void pr
    ~Graph();
};

void Graph::printStudentsNotInSocialCircle() {
    

      for(int i=0; i < MAXVEX; i++) {
        
           Node * temp = adjList[i]->next;
           bool visited[MAXVEX];
               for(int k=0; k< MAXVEX; k++) {
                 visited[k] = false;
               }
               while(temp != NULL) {
                    Node * personsFriend = adjList[temp->index];
                       while (personsFriend != NULL) {
                              
                                visited[personsFriend->index] = true;

                        personsFriend = personsFriend->next;
                       }
                    temp = temp->next;
               }
           cout << endl  << "People not in social circle of " << adjList[i]->data << " are :\n";
               for(int j=0; j< MAXVEX; j++) {
                            if(visited[j] == false) {
                                cout << adjList[j]->data << ", " ;
                            }
                }
      }
}

void Graph::setIndex() {
    for(int i=0; i < MAXVEX; i++){
         Node * temp = adjList[i]->next;
            while(temp != NULL){
                    for(int j=0; j < MAXVEX; j++){
                         if(temp->data == adjList[j]->data){
                               temp->index = adjList[j]->index;
                         }
                    }
                temp = temp->next;
            }
          
    }
}



//below function is used to display the common profiles of two users
void Graph::displayCommonProfiles(int a, int b) {
  bool visited[MAXVEX] ;
  int count = 0;
   a = a - 2001;
   b = b - 2001;
     for(int i=0; i< MAXVEX;i++){ visited[i] = false; }
   if(a < 0 || b < 0 || a >= MAXVEX || b >= MAXVEX) {
       cout << "Invalid input" << endl;
       return;
    }
    Node * temp1 = adjList[a]->next;
    
    cout << "\nCommon profiles between " << adjList[a]->data << " and " << adjList[b]->data << " are: " << endl;
    while(temp1 != NULL) {
        Node * person1Friends = adjList[temp1->index];
        
            while( person1Friends != NULL) {
              Node * temp2 = adjList[b]->next;
                   while(temp2 != NULL) {
                          Node * person2Friends = adjList[temp2->index];
                          // cout << person2Friends->index << "*";
                          // cout << temp2->index << " ";
                          while(person2Friends != NULL) {
                                if(person1Friends->index == person2Friends->index){
                              // cout << person1Friends->index << "*" << person2Friends->index << " ";
                                   if(!visited[person1Friends->index]){
                                        cout << count << ") "  << person1Friends->data << endl;
                                       visited[person1Friends->index] = true; 
                                       count++;
                                   }
                                }
                                person2Friends = person2Friends->next;
                          }
                        temp2 = temp2->next;
                   }
                person1Friends = person1Friends->next;
            }
          temp1 = temp1->next;
    }
}


void Graph::socialDistancebtw(int src, int des){
    src -= 2001;
    des -= 2001;
    if(src < 0 || des < 0 || src >= MAXVEX || des >= MAXVEX){
       cout << "Invalid input" << endl;
       return;
    }

    int visited[MAXVEX];
    for(int i=0; i< MAXVEX;i++){ visited[i] = 0; }
    queue<int> q;
    q.push(src);
    visited[src] = 1;
    while(!q.empty()){
        int temp = q.front();
        q.pop();
        Node * tempNode = adjList[temp];
        while(tempNode != NULL) {
            if( visited[tempNode->index] == 0 ) {
                visited[tempNode->index] = visited[temp] + 1;
                q.push(tempNode->index);
            }

            tempNode = tempNode->next;
        }
    }
    cout << "\nSocial distance between " << adjList[src]->data << " and " << adjList[des]->data << " is " << visited[des] - 1 << endl;
}


Graph::Graph(): V(MAXVEX) {
    adjList = new Node*[V];
      for(int i=0; i< V; i++){
        adjList[i] = NULL;
      }
       
}

void Graph::printGraph(){
    // cout << adjList[0]->data << endl;
    Node * temp;
  for(int i=0; i<V; i++){
    temp = adjList[i];
    // cout << adjList[i]->data;
    cout << "Adjacency list of vertex " << i << " is: ";
    while(temp){
      cout << temp->data << " ";
      // adjList[0]->data;
      temp = temp->next;
    }
    cout << endl;
  }
}

void Graph::addVertexAtRowHead(int v, int data) {
    adjList[v] = new Node(data, v);
}

void Graph::addFriend(int v, int data) {
      Node * temp = adjList[v];
      Node * newNode = new Node(data);
         while(temp->next != NULL){
             temp = temp->next;
         }
        temp->next = newNode;
 
}

void splitString(string s, Graph &g) {
         string source = "";
         string destination =  "";
           int valueNo = 1;
           static int graphIndex = 0;
    for(int i=0; i<s.length(); i++) {
         if(s[i] == ':'){
            //  g.adjList[i]->index = i;
             g.addVertexAtRowHead(graphIndex, stoi(source));  //all member are added to the graph
             graphIndex++;  //indices of the students
             valueNo++; 
             i++;   //because there is a space in file after ":"
         }
          else if(s[i] == ' '){
                g.addFriend(graphIndex-1, stoi(destination));
                destination = "";
         }else{
            switch (valueNo)
               {
                   case 1:{
                       source += s[i];
                   }break;
                   case 2:{
                       destination += s[i];
                   }break;
               }
         }
    }
}

void readData(Graph &g){
    fstream iFile;
    iFile.open("./friends.txt");
      if(iFile.is_open()){
              string data;
          while(!iFile.eof()){
              getline(iFile, data);
            //   cout << data;
              splitString(data, g);
            //   cout << endl;
          }
      }else{
            cout << "File not found" << endl;
      }
    iFile.close();
     g.setIndex();
}


int Graph::biggestSocialCircle() {
    int personIdWithBiggestSocialCircle;
    int maxCount =0;
        for(int i=0; i< MAXVEX; i++) {
        bool visited[MAXVEX];
           for(int j=0; j< MAXVEX;j++){ visited[j] = false; }
            int count = 0;
            Node * temp = adjList[i]->next;
               while(temp != NULL) {
                    Node * personsFriend = adjList[temp->index];
                        while(personsFriend != NULL) {
                                 if(!visited[personsFriend->index]) {
                                        count++;
                                        // cout << count << ") " << personsFriend->data << endl;
                                        visited[personsFriend->index] = true;
                                 }
                            personsFriend = personsFriend->next;
                        }
                    temp = temp->next;
               }
               if(count > maxCount) {
                   maxCount = count;
                   personIdWithBiggestSocialCircle = adjList[i]->data;
   
               }
        }
 return personIdWithBiggestSocialCircle;
}


Graph::~Graph(){
    for(int i=0; i<V; i++){
        Node *temp = adjList[i];
        while(temp){
            Node *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
    }
    delete [] adjList;
}