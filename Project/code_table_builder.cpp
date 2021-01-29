#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

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

void build_code_table(treenode* root, string str, std::unordered_map<int, string>&codeTable)
{
	if (root == NULL)
		return;
	build_code_table(root->left, str + "0",codeTable);
	build_code_table(root->right, str + "1",codeTable);

	if (root->data >= 0)
		codeTable[root->data] = str;


}