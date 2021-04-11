#include "helper.cpp"

#include <iostream>
#include <fstream>
#include <list>

int main(){
	std::ifstream file("code.txt", std::ios::out | std::ios::binary);
    if (!file){
        std::cerr << "Uh oh, Text.txt could not be opened for reading!" << '\n';
    }
	std::ofstream res_file("output.txt", std::ios::out | std::ios::binary);
    if(!res_file){
        std::cerr << "Uh oh, output.txt could not be opened for writing!" << '\n';
    }

	int n, n_sym;
	char s;
	std::map<char, int> table;
    std::map<char, int>::iterator it;
	file.read((char*)&n, sizeof(n));
	while (n > 0){
		file.read((char*)&s, sizeof(s));
		file.read((char*)&n_sym, sizeof(n_sym));
        --n;
        table[s] = n_sym;
	}   /// creat table

    std::list<Node*> l;
	for (it = table.begin(); it != table.end(); it++){
        Node *p = new Node(it->first, it->second);  ///char s_ = it->first nt key_ = it->second
        l.push_back(p);
	}
	while (l.size() != 1){
		l.sort(comp);
		Node *left_node = l.front();
		l.pop_front();
		Node *right_node = l.front();
		l.pop_front();
		Node *new_node = new Node(left_node, right_node);
		l.push_back(new_node);
	}

	Node *root = l.front();
    tree_go(root);

	char byte;
	int count = 0;
	Node *p = root;
	byte = file.get();

	while (!file.eof()){
		bool bit = byte & (1 << (7 - count));
		if (bit) {
            p = p->right_;
        }
		else {
            p = p->left_;
        }
		if (p->left_ == nullptr && p->right_ == nullptr){
			res_file << p->s_;
			p = root;
		}
		count++;
		if (count == 8){
			count = 0;
			byte = file.get();
		}
	}

    file.close();
    res_file.close();

	return 0;
}