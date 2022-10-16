//Luke Kaplan
//sjd7wr
//10-12-22
//AVLNode.h

#ifndef AVLNODE_H
#define AVLNODE_H
#include <string>
using namespace std;

class AVLNode {
    AVLNode();
    ~AVLNode();

    string value;
    AVLNode* left;
    AVLNode* right;
    int height;
    int balanceFactor;

    friend class AVLTree;
};

#endif
