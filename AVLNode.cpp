//Luke Kaplan
//sjd7wr
//10-12-22
//AVLNode.cpp

#include "AVLNode.h"
#include <string>
using namespace std;

AVLNode::AVLNode() {
    value = "?";
    left = NULL;
    right = NULL;
    height = 0;
    balanceFactor = 0;
}

AVLNode::~AVLNode() {
    delete left;
    delete right;
    left = NULL;
    right = NULL;
}
