#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include "code_table_builder.h"

using namespace std;



class Fourwayheap {

private:

	vector <node> heap;

	int fisrtChild(int parent);

	int secondChild(int parent);

	int thirdChild(int parent);

	int fourthChild(int parent);

	int parent(int child);

	void siftUp(int index);

	void siftDown(int index);

public:

	Fourwayheap()

	{}

	void insert(node& newNode, treenode* temp);

	void deleteMin();

	node extractMin();

	int Size();

	int findMin(int fisrtChild, int secondChild, int thirdChild, int fourthChild);

};

int Fourwayheap::Size()
{

	return heap.size();

}


void Fourwayheap::insert(node& newNode, treenode* temp)
{
	if (heap.size() == 0)
	{
		heap.push_back(node());
		heap[heap.size() - 1].data = -1;
		heap[heap.size() - 1].freq = -1;
		heap[heap.size() - 1].root = NULL;
		heap.push_back(node());
		heap[heap.size() - 1].data = -1;
		heap[heap.size() - 1].freq = -1;
		heap[heap.size() - 1].root = NULL;
		heap.push_back(node());
		heap[heap.size() - 1].data = -1;
		heap[heap.size() - 1].freq = -1;
		heap[heap.size() - 1].root = NULL;
	}
	heap.push_back(node());
	heap[heap.size() - 1].data = newNode.data;
	heap[heap.size() - 1].freq = newNode.freq;
	heap[heap.size() - 1].root = temp;
	siftUp(heap.size() - 1);
}

void Fourwayheap::deleteMin()
{

	if (heap.size() == 3)

	{

		cout << "Heap is Empty" << endl;

		return;

	}

	heap[3] = heap.at(heap.size() - 1);

	heap.pop_back();
	siftDown(3);

}


node Fourwayheap::extractMin()
{
	node p;
	p.data = 0;
	p.freq = 0;

	if (heap.size() == 0)
		return p;
	else
		return heap[3];

}


int Fourwayheap::fisrtChild(int parent)
{

	unsigned int fisrtChild = 4 * (parent - 3) + 4;

	if (fisrtChild < heap.size())

		return fisrtChild;

	else

		return -1;

}


int Fourwayheap::secondChild(int parent)
{

	unsigned int secondChild = 4 * (parent - 3) + 5;

	if (secondChild < heap.size())

		return secondChild;

	else

		return -1;

}

int Fourwayheap::thirdChild(int parent)
{

	unsigned int thirdChild = 4 * (parent - 3) + 6;

	if (thirdChild < heap.size())

		return thirdChild;

	else

		return -1;

}

int Fourwayheap::fourthChild(int parent)
{

	unsigned int fourthChild = 4 * (parent - 3) + 7;

	if (fourthChild < heap.size())

		return fourthChild;

	else

		return -1;

}


int Fourwayheap::parent(int child)
{

	int p = (child - 4) / 4 + 3;

	if (child == 0)

		return -1;

	else

		return p;

}


void Fourwayheap::siftUp(int in)
{
	node temp;

	if (in > 3 && parent(in) >= 3 && heap[parent(in)].freq > heap[in].freq)
	{

		temp = heap[parent(in)];

		heap[parent(in)] = heap[in];

		heap[in] = temp;

		siftUp(parent(in));

	}

}

int Fourwayheap::findMin(int fisrtChild, int secondChild, int thirdChild, int fourthChild)
{
	int min = fisrtChild;

	if ((secondChild > 3) && (heap[secondChild].freq < heap[min].freq))
		min = secondChild;
	if ((thirdChild > 3) && (heap[thirdChild].freq < heap[min].freq))
		min = thirdChild;
	if ((fourthChild > 3) && (heap[fourthChild].freq < heap[min].freq))
		min = fourthChild;

	return min;
}


void Fourwayheap::siftDown(int in)
{

	node temp;

	int child1 = fisrtChild(in);

	int child2 = secondChild(in);

	int child3 = thirdChild(in);

	int child4 = fourthChild(in);

	int child = findMin(child1, child2, child3, child4);

	if ((child > 3) && (heap[in].freq > heap[child].freq))
	{
		temp = heap[in];

		heap[in] = heap[child];

		heap[child] = temp;

		siftDown(child);
	}

}

Fourwayheap build_4way_heap(unordered_map<int, int>& freqTable)
{
	Fourwayheap h;
	struct node newNode;
	treenode* root = NULL;
	for (auto i = freqTable.begin(); i != freqTable.end(); i++) {
		root = new treenode(i->first, i->second);
		newNode.data = i->first;
		newNode.freq = i->second;
		h.insert(newNode, root);
	}
	return h;
}

void build_tree_using_4way_heap(unordered_map<int, int>& freqTable, unordered_map<int, string>& codeTable)
{
	Fourwayheap h;
	h = build_4way_heap(freqTable);
	node p, q, temp;
	treenode* left = NULL, * right = NULL, * newNode = NULL;
	string str;
	while (h.Size() > 4)
	{

		p = h.extractMin();
		left = p.root;
		//cout << "first=" << p.freq << "   " << p.root << endl;
		h.deleteMin();

		q = h.extractMin();
		//cout << "second=" << q.freq << "   " << q.root << endl;
		right = q.root;
		h.deleteMin();

		newNode = new treenode(-1, p.freq + q.freq);

		newNode->left = left;
		newNode->right = right;
		temp.data = -1;
		temp.freq = p.freq + q.freq;
		h.insert(temp, newNode);

	}

	build_code_table(newNode, "", codeTable);
}
