#include <iostream>
#include <fstream>
#include  <clocale>
#include <Windows.h>
#include <list>
#include <map>

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
};

void write_table_to_file(std::map<char, int> &table){

    std::ofstream file_res("code.txt");
    if(!file_res){
        std::cerr << "Uh oh, code.txt could not be opened for writing!" << '\n';
        exit(1);
    }

    int* point = &table;
    for(int i = 0; i < 255; ++i){
        if(point[i] != 0){
            file_res << char(i) << point[i];
        }
    }
}

int main() {

    setlocale(LC_ALL,"Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::ifstream file("text.txt");
    if (!file){
        std::cerr << "Uh oh, Text.txt could not be opened for reading!" << '\n';
        exit(1);
    }

    std::map<char, int> table;
    std::map<char, int>:: iterator it;

    char file_res;
    while(!file.eof()) {
        file >> file_res;
        table[file_res]++;
    }
    write_table_to_file(table);
    /*Node tree;
    for(int i = 0; i < 255; ++i){
        if(table[i] != 0){
          tree.key_ = table[i];
          tree.s_ = char(i);
        }
    }*/
    std::list<Node*> l;
    for(it = table.begin(); it != table.end(); ++it){
        Node *p = new Node(it->first, it->second);  ///char s = it->first nt key = it->second
        l.push_back(p);
    }

    return 0;
}

