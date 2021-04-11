#ifndef HELPER_H
#define HELPER_H

class Node{
public:
    char s_;    ///symbol
    int key_;   /// amount symbols
    Node *left_, *right_;   ///pointers on left_ and right_

    Node();
    Node(char , int );
    Node (Node *, Node *);
    ~Node();
};

void tree_go(Node *);
bool comp (const Node *, const Node *);

#endif
