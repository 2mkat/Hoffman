#include <iostream>
#include <fstream>
#include  <clocale>
#include <Windows.h>
#include <list>
#include <map>
#include <vector>

std::vector<bool> cipher;
std::map<char, std::vector<bool>> code;

class Node{
public:
    char s_;    ///symbol
    int key_;   /// amount symbols
    Node *left_, *right_;   ///pointers on left and right

    Node(){
        key_ = 0;
        s_ = ' ';
        left_ = nullptr;
        right_ = nullptr;
    }   /// default constructor
    Node(char s, int key){
        s_ = s;
        key_ = key;
        left_ = nullptr;
        right_ = nullptr;
    }
    Node (Node *left, Node *right){
        key_ = left->key_ + right->key_;    /// merging to symbols and sum it
        left_ = left;
        right_ = right;
    }
    ~Node(){
        delete[] left_;
        delete[] right_;
    }
    friend std::ostream& operator<<(std::ostream& out, Node& c1){
        out << c1.s_ << " " << c1.key_ << '\n';
        return out;
    }
};
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

int main() {

    setlocale(LC_ALL,"Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::ofstream file_res("code.txt", std::ios::out | std::ios::binary);
    if(!file_res){
        std::cerr << "Uh oh, code.txt could not be opened for writing!" << '\n';
        exit(1);
    }

    std::ifstream file("text.txt", std::ios::out | std::ios::binary);
    if (!file){
        std::cerr << "Uh oh, Text.txt could not be opened for reading!" << '\n';
        exit(1);
    }

    std::map<char, int> table;
    std::map<char, int>:: iterator it;

    char s;
    while(file >> s) {
        table[s]++;
    }
    int count = 0;
    for (it = table.begin(); it != table.end(); it++){
        if (it->second != 0){
            ++count;
        }
    }
    file_res << count;
    for(it = table.begin(); it != table.end(); ++it){
        file_res << it->first << it->second;
    }

    std::list<Node*> l;
    for(it = table.begin(); it != table.end(); ++it){
        Node *p = new Node(it->first, it->second);  ///char s = it->first nt key = it->second
        l.push_back(p);
    }

    while(l.size() != 1) {
        l.sort(comp);   //make one sort and put on value
        Node *left_node = l.front();
        l.pop_front();
        Node *right_node = l.front();
        l.pop_front();
        Node *new_node = new Node(left_node, right_node);
        l.push_back(new_node);
    }

    Node *root = l.front();
    tree_go(root);  ///обход дерева леворекурсивный. Обходим дерево и все листы кладем в новую мапу

    char tp;
    std::vector<bool> tmp;
    count = 0;

    file.clear();   /////после чтения за концом файла, поток перейдет в ошибочное состояние, clear сбрасывает ошибки
    file.seekg(0); ///return pointer file to start
    while(file >> s){
        tmp = code[s];
        for(int i = 0; i < tmp.size(); ++i){
            std::cout << tmp[i];
        }
        for(int i = 0; i < tmp.size(); ++i){
            tp = tp | tmp[i] << (7 - count);
            ++count;
            if(count == 8){
                count = 0;
                file_res << tp;
                tp = 0;
            }
        }
    }

    file.close();
    file_res.close();

    return 0;
}