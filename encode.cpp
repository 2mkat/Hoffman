#include <iostream> 
#include <fstream>
#include <vector>
#include <map>
#include <list>

std::vector<bool> code;
__attribute__((unused)) std::map<char, std::vector<bool>> buf;

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
bool comp (const Node *c1, const Node *c2){
    return c1->key_ < c2->key_;
}
void tree_go(Node *root){
	if (root->left_ != nullptr) {
		code.push_back(0);
        tree_go(root->left_);
	}
	if (root->right_ != nullptr){
		code.push_back(1);
        tree_go(root->right_);
	}
	if (root->right_ == nullptr && root->left_ == nullptr){
		buf[root->s_] = code;
	}
	if (!code.empty()) {
        code.pop_back();
    }
}

int main(){
	std::ifstream file("code.txt", std::ios::out | std::ios::binary);
    if (!file){
        std::cerr << "Uh oh, Text.txt could not be opened for reading!" << '\n';
        exit(1);
    }

	std::ofstream res_file("output.txt", std::ios::in | std::ios::binary);
    if(!res_file){
        std::cerr << "Uh oh, output.txt could not be opened for writing!" << '\n';
        exit(1);
    }

	int n, n_sym;
	char s;
	std::map<char, int> table;

	file.read((char*)&n, sizeof(n));
	while (n > 0){
		file.read((char*)&s, sizeof(s));
		file.read((char*)&n_sym, sizeof(n_sym));
        n -= 40;
        table[s] = n_sym;
	}   /// creat table

    std::list<Node*> l;
	std::map<char, int>::iterator it;

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