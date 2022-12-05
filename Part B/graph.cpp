#include "./graph.h"

int main(){
Graph g;
readData(g);
// g.countsocialcircle();
// g.printGraph();
g.displayCommonProfiles(20, 304);
g.socialDistancebtw(0,37);
cout << g.biggestSocialCircle();
return EXIT_SUCCESS;
}