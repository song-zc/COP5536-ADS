#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string> 
#include <bitset>

using namespace std;

struct treenode {

	int data;
	treenode* left, * right;
	treenode()
	{
		this->data = -1;
		left = right = NULL;
	}
};

void printTree1(treenode* root)
{
	if (root == NULL)
		return;
	printTree1(root->left);
	cout << root->data << "  ";
	printTree1(root->right);




}

void printTree2(treenode* root)
{
	if (root == NULL)
		return;
	cout << root->data << "  ";
	if (root->left!=NULL)
		cout <<"left"<< root->left->data << "  "; 
	if (root->right!=NULL)
		cout << "right"<<root->right->data << "  ";
	cout << endl;
	printTree2(root->left);
	printTree2(root->right);




}

int main(int argc, char* argv[])
{
	unordered_map<int, string> decodeTable;
	ifstream inFile;
	inFile.open(argv[2]);
	string fileLine,t1,t2;
	int t,pos;
	while (getline(inFile, fileLine))
	{
		pos = fileLine.find(" ");
		t1 = fileLine.substr(0,pos);
		t2= fileLine.substr(pos,fileLine.length());
		t = std::stoi(t1);
		//cout << t << " " << t2 << endl;
		decodeTable[t] = t2;
	}
	inFile.close();
	treenode* root=new treenode(), * temp;

	for (auto i = decodeTable.begin(); i != decodeTable.end(); i++) {
		temp = root;
		unsigned int j;
		for (j = 1; j < i->second.length(); j++)
		{
			//cout << "j=" << i->second[j];
			if (i->second[j] == '0')
			{
				if (temp->left == NULL)
					temp->left = new treenode();
				temp = temp->left;
			}
			else
			{
				if (temp->right == NULL)
					temp->right = new treenode();
				temp = temp->right;
			}
		}
		temp->data = i->first;
		//cout << temp->data<<endl;
	}

	//printTree1(root);
	//cout << endl;
	//printTree2(root);
	//cout << endl;

	inFile.open(argv[1], std::ios::in | std::ios::binary);
	char c;
	bitset<8> b;

	ofstream outFile;
	outFile.open("decoded.txt", std::ios::out | std::ios::trunc);

	temp = root;

	while (inFile.get(c))
	{
		bitset<8> b(c);
		//cout << b << " ";
		for (int j = 7; j >=0 ; j--)
		{
			//cout << b[j];
			if ((temp->data) != -1)
			{
				//cout << temp->data;
				outFile << temp->data << endl;
				temp = root;
			}
			if ((b[j] & 1) == 0)
			{
				temp = temp->left;
			}
			else
			{
				temp = temp->right;
			}
			if ((temp->data) != -1)
			{
				//cout << temp->data;
				outFile << temp->data << endl;
				temp = root;
			}
		}
	}
	inFile.close();
	outFile.close();
	cout << "finish" << endl;
}


