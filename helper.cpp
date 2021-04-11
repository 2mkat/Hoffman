#include "helper.h"

#include <map>
#include <vector>

std::vector<bool> cipher;
std::map<char, std::vector<bool>> code;

Node::Node(){
    key_ = 0;
    s_ = ' ';
    left_ = nullptr;
    right_ = nullptr;
}   /// default constructor

Node::Node(char s, int key){
    s_ = s;
    key_ = key;
    left_ = nullptr;
    right_ = nullptr;
}
Node::Node (Node *left, Node *right){
    key_ = left->key_ + right->key_;    /// merging to symbols and sum it
    left_ = left;
    right_ = right;
}
Node::~Node(){
    delete[] left_;
    delete[] right_;
}

bool comp (const Node *c1, const Node *c2){
    return c1->key_ < c2->key_;
}

void tree_go(Node *head){
    if(head->left_ != nullptr){
        cipher.push_back(0);
        tree_go(head->left_);
    }
    if(head->right_ != nullptr){
        cipher.push_back(1);
        tree_go(head->right_);
    }
    if (head->left_ == nullptr && head->right_ == nullptr){
        code[head->s_] = cipher;
    }
    if(!cipher.empty()){
        cipher.pop_back();
    }
}