#include"temp.cpp"

void Insertion (BPTree& Btree) {
    Btree.insert(1);
    Btree.insert(4);
    Btree.insert(7);
    Btree.insert(10);
    Btree.insert(17);
    Btree.insert(21);
    Btree.insert(31);
    Btree.insert(25);
    Btree.insert(19);
    Btree.insert(20);
    Btree.insert(28);
    Btree.insert(42);
    Btree.insert(43);

}
int main() {
    BPTree Btree;
    Insertion(Btree);
    Btree.display(Btree.getRoot());
    return 0;
}