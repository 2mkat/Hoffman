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
    std::ifstream file("text.txt");

    file >> buff;
    //std::cout << buff << std::endl;


    return 0;
}

