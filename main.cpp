#include <iostream>
#include <fstream>

/*
class node{
private:
    char sym;
    int key;

};*/

int main() {

    setlocale( LC_ALL, "rus");
    char buff[50];
    std::ifstream fin("text.txt");

    fin >> buff;
    std::cout << buff << std::endl;


    return 0;
}

