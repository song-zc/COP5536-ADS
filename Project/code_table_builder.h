#include <unordered_map>
#include <vector>
#include <string>

struct treenode {
	int data;
	int freq;
	treenode* left, * right;
	treenode(int data, int freq)
	{
		this->data = data;
		this->freq = freq;
		left = right = NULL;
	}
};

struct node
{
	struct node* left, * right;
	int data;
	int freq;
	treenode* root;
};

void build_code_table(treenode* root, std::string str, std::unordered_map<int, std::string>& codeTable);
