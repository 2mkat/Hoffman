#include <iostream>
#include <fstream>
#include  <clocale>
#include <Windows.h>

class Node{
public:
    char s_;
    int key_;
    Node *left_, *right_;
    Node(){
        key_ = 0;
        s_ = ' ';
        left_ = nullptr;
        right_ = nullptr;
    }
    ~Node(){
        delete[] left_;
        delete[] right_;
    }
};

void write_table_to_file(int &table){

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

void creat_table (int &table, std::string str){
    int* point = &table;
    for(auto x : str){
        point[x]++;
    }
}

int main() {

    setlocale(LC_ALL,"Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string file_result;
    std::ifstream file("text.txt");

    if (!file){
        std::cerr << "Uh oh, Text.txt could not be opened for reading!" << '\n';
        exit(1);
    }

    int table[255] = {0};

    while(!file.eof()) {
        file >> file_result;
        creat_table(*table, file_result);
    }
    Node tree;
    write_table_to_file(*table);
    for(int i = 0; i < 255; ++i){
        if(table[i] != 0){
          tree.key_ = table[i];
          tree.s_ = char(i);
        }
    }

    return 0;
}

