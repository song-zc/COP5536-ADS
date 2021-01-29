#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include "code_table_builder.h"

using namespace std;

class PairingNode
{

public:
		
	int data, freq;

	PairingNode* leftChild;

	PairingNode* nextSibling;

	PairingNode* prevSibling;
	
	treenode* root;

	PairingNode(int data, int freq, treenode* root)
	{
		this->root = root;

		this->data = data;

		this->freq = freq;

		leftChild = NULL;

		nextSibling = NULL;

		prevSibling = NULL;

	}

};


class PairingHeap
{

private:

	PairingNode* root;

	void meld(PairingNode*& first, PairingNode* second);

	PairingNode* merge(PairingNode* firstSibling);

public:

	int size = 0;

	PairingHeap();

	bool isEmpty();

	treenode* extractMin();

	void insert(node&newNode, treenode* root);

	void deleteMin();

};



PairingHeap::PairingHeap()
{

	root = NULL;

}


void PairingHeap::insert(node&newNode, treenode* temp)
{

	PairingNode *newPairingNode = new PairingNode(newNode.data, newNode.freq, temp);

	if (root == NULL)

		root = newPairingNode;

	else

		meld(root, newPairingNode);
}


treenode* PairingHeap::extractMin()
{

	return this->root->root;

}


void PairingHeap::deleteMin()
{

	if (isEmpty())
	{

		cout << "The Heap is Empty" << endl;

		return;

	}

	PairingNode* oldRoot = root;

	if (root->leftChild == NULL)
		root = NULL;

	else
		root = merge(root->leftChild);

	delete oldRoot;

}



bool PairingHeap::isEmpty()
{

	return root == NULL;

}

void PairingHeap::meld(PairingNode*& first, PairingNode* second)
{

	if (second == NULL)

		return;

	if (second->freq <= first->freq)
	{

		second->prevSibling = first->prevSibling;

		first->prevSibling = second;

		first->nextSibling = second->leftChild;

		if (first->nextSibling != NULL)

			first->nextSibling->prevSibling = first;

		second->leftChild = first;

		first = second;

	}

	else
	{

		second->prevSibling = first;

		first->nextSibling = second->nextSibling;

		if (first->nextSibling != NULL)

			first->nextSibling->prevSibling = first;

		second->nextSibling = first->leftChild;

		if (second->nextSibling != NULL)

			second->nextSibling->prevSibling = second;

		first->leftChild = second;

	}

}


PairingNode* PairingHeap::merge(PairingNode* firstSibling)
{

	if (firstSibling->nextSibling == NULL)

		return firstSibling;

	static vector<PairingNode*> treeArray(5);

	int numSiblings = 0;

	for (; firstSibling != NULL; numSiblings++)
	{

		if (numSiblings == treeArray.size())

			treeArray.resize(numSiblings * 2);

		treeArray[numSiblings] = firstSibling;

		firstSibling->prevSibling->nextSibling = NULL;

		firstSibling = firstSibling->nextSibling;

	}

	if (numSiblings == treeArray.size())

		treeArray.resize(numSiblings + 1);

	treeArray[numSiblings] = NULL;

	int i = 0;

	for (; i + 1 < numSiblings; i += 2)

		meld(treeArray[i], treeArray[i + 1]);

	int j = i - 2;

	if (j == numSiblings - 3)

		meld(treeArray[j], treeArray[j + 2]);

	for (; j >= 2; j -= 2)

		meld(treeArray[j - 2], treeArray[j]);

	return treeArray[0];

}


PairingHeap build_pairing_heap(unordered_map<int, int>& freqTable)
{
	PairingHeap h;
	struct node newNode;
	treenode* root = NULL;
	for (auto i = freqTable.begin(); i != freqTable.end(); i++) {
		root = new treenode(i->first, i->second);
		newNode.data = i->first;
		newNode.freq = i->second;
		h.insert(newNode, root);
		h.size++;
	}
	return h;
}

void build_tree_using_pairing_heap(unordered_map<int, int>& freqTable, unordered_map<int, string>& codeTable)
{
	PairingHeap h;
	h = build_pairing_heap(freqTable);
	node temp;
	treenode* left = NULL, * right = NULL, * newNode = NULL;
	string str;
	while (h.size>1)
	{

		left = h.extractMin();
		//cout << "first=" << left->freq << "   "  << endl;
		h.deleteMin();

		right = h.extractMin();
		//cout << "second=" << right->freq << "   "  << endl;
		h.deleteMin();

		newNode = new treenode(-1, left->freq + right->freq);

		newNode->left = left;
		newNode->right = right;
		temp.data = -1;
		temp.freq = left->freq + right->freq;
		h.insert(temp,newNode);
		h.size--;

	}
	build_code_table(newNode, "", codeTable);
}