#include "helper.cpp"

#include <iostream>
#include <fstream>
#include <list>

int main() {
    std::ofstream file_res("code.txt", std::ios::in | std::ios::binary);
    if(!file_res){
        std::cerr << "Uh oh, code.txt could not be opened for writing!" << '\n';
    }
    std::ifstream file("text.txt", std::ios::out | std::ios::binary);
    if (!file){
        std::cerr << "Uh oh, Text.txt could not be opened for reading!" << '\n';
    }

    std::map<char, int> table;
    std::map<char, int>:: iterator it;
    char s;
    while(!file.eof()) {
        s = file.get();
        table[s]++;
    }   ///count symbols

    std::list<Node*> l;
    for(it = table.begin(); it != table.end(); ++it){
        Node *p = new Node(it->first, it->second);  ///char s_ = it->first nt key_ = it->second
        l.push_back(p);
    }
    while(l.size() != 1) {
        l.sort(comp);
        Node *left_node = l.front();
        l.pop_front();
        Node *right_node = l.front();
        l.pop_front();
        Node *new_node = new Node(left_node, right_node);
        l.push_back(new_node);
    }
    Node *root = l.front();
    tree_go(root);  ///обход дерева леворекурсивный. Обходим дерево и все листы кладем в новую мапу

    int count = 0;
    for (it = table.begin(); it != table.end(); it++){
        if (it->second != 0){
            ++count;
        }
    }
    file_res.write((char*)(&count), sizeof(count));
    for(it = table.begin(); it != table.end(); ++it){
        file_res.write((char*)(&it->first), sizeof(it->first));
        file_res.write((char*)(&table[it->first]), sizeof(table[it->first]));
    }

    char tp;
    std::vector<bool> tmp;
    count = 0;

    file.clear();   /////после чтения за концом файла, поток перейдет в ошибочное состояние, clear сбрасывает ошибки
    file.seekg(0); ///return pointer file to start
    while(!file.eof()){
        s = file.get();
        tmp = code[s];
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

   std::map<char, std::vector<bool>>:: iterator it_c;
    for(it_c = code.begin(); it_c != code.end(); ++it_c){
        std::cout << it_c->first << ": ";
        for(int i = 0; i < it_c->second.size(); ++i){
            std::cout << it_c->second[i];
        }
        std::cout << '\n';
    }

    file.close();
    file_res.close();

    return 0;
}
