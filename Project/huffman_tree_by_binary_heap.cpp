#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include "code_table_builder.h"

using namespace std;

class BinaryHeap
{

public:

	vector <node> heap;

	int left(int parent);

	int right(int parent);

	int parent(int child);

	void siftUP(int index);

	void siftDown(int index);

	BinaryHeap()

	{}

	void insert(node&newNode,treenode*);

	void deleteMin();

	node extractMin();

	int Size();

};

int BinaryHeap::Size()
{

	return heap.size();

}


void BinaryHeap::insert(node& newNode, treenode* temp)
{

	heap.push_back(node());
	heap[heap.size() - 1].data = newNode.data;
	heap[heap.size() - 1].freq = newNode.freq;
	heap[heap.size() - 1].root = temp;
	siftUP(heap.size() - 1);

}

void BinaryHeap::deleteMin()
{

	if (heap.size() == 0)
	{
		cout << "Heap is Empty" << endl;
		return;
	}

	heap[0] = heap.at(heap.size() - 1);

	heap.pop_back();

	siftDown(0);

}


node BinaryHeap::extractMin()
{
	node p;
	p.data = -1;
	p.freq = -1;

	if (heap.size() == 0)
		return p;
	else
		return heap.front();

}



int BinaryHeap::left(int parent)
{

	unsigned int l = 2 * parent + 1;

	if (l < heap.size())

		return l;

	else

		return -1;

}


int BinaryHeap::right(int parent)
{

	unsigned int r = 2 * parent + 2;

	if (r < heap.size())

		return r;

	else

		return -1;

}


int BinaryHeap::parent(int child)
{

	int p = (child - 1) / 2;

	if (child == 0)

		return -1;

	else

		return p;

}


void BinaryHeap::siftUP(int in)
{

	node temp;

	if (in >= 0 && parent(in) >= 0 && heap[parent(in)].freq > heap[in].freq)
	{

		temp = heap[parent(in)];

		heap[parent(in)] = heap[in];

		heap[in] = temp;

		siftUP(parent(in));

	}

}



void BinaryHeap::siftDown(int in)
{

	node temp;

	int child = left(in);

	int child1 = right(in);

	if (child >= 0 && child1 >= 0 && heap[child].freq > heap[child1].freq)
		child = child1;

	if (child > 0 && heap[in].freq > heap[child].freq)
	{

		temp = heap[in];

		heap[in] = heap[child];

		heap[child] = temp;

		siftDown(child);

	}
}

BinaryHeap build_binary_heap(unordered_map<int, int>& freqTable)
{
	BinaryHeap h;
	struct node newNode;
	treenode* root = NULL;
	for (auto i = freqTable.begin(); i != freqTable.end(); i++) {
		newNode.left = NULL;
		newNode.right = NULL;
		root = new treenode(i->first, i->second);
		newNode.data = i->first;
		newNode.freq = i->second;
	    h.insert(newNode,root);
	}
	return h;
}



void build_tree_using_binary_heap(unordered_map<int, int>& freqTable, unordered_map<int, string>& codeTable)
{
	BinaryHeap h;
	h=build_binary_heap(freqTable);
	node p,q,temp;
	treenode *left = NULL, *right = NULL, *newNode = NULL;
	string str;
	while (h.Size() > 1)
	{

		p = h.extractMin();
		left = p.root;
		//cout << "first=" << p.freq<<"   "<<p.root << endl;
		h.deleteMin();


		q = h.extractMin();
		//cout <<"second="<< q.freq<<"   "<<q.root<<endl;
		right = q.root;
		h.deleteMin();

		newNode = new treenode(-1,p.freq + q.freq);

		newNode->left = left;
		newNode->right = right;
		temp.data = -1;
		temp.freq = p.freq + q.freq;
		h.insert(temp,newNode);

	}
	build_code_table(newNode, "",codeTable);
}
