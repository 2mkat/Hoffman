#include <iostream>
#include <fstream>
#include  <clocale>
#include <Windows.h>

/*
class node{
private:
    char sym;
    int key;

};*/

void creat_table (int &table, std::string str){
    std::cout << str << '\n';
    int* point = &table;
    for(auto x : str){
        point[x]++;
    }
    //std::cout << table[4] << '\n';
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

    for(int i = 0; i < 255; ++i){
        std::cout << i << ": " << table[i] << '\n';
    }

    return 0;
}

