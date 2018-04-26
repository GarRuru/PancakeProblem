#include <iostream>
#include <string>
#define MAX_PANCAKES 16
#define MAX_HEAP_ARRAYS 100
using namespace std;

struct Node {
	
	int state[MAX_PANCAKES],
		g,
		h;
};

void swapNode(Node *x, Node *y) { Node t; t = *x; *x = *y; *y = t; }

class Heap {
public:
	Heap(void);
	~Heap(void);
	int f(Node &node);
	int parent(int index);
	int left(int index);
	int right(int index);
	void insert(int state[], int g, int h);
	Node getTop();
	void minHeapify(int index);
	bool isEmpty();

private:
	Node *heapArray;
	int heapSize;
};

Heap::Heap()
	: heapSize(0), heapArray(new Node[MAX_HEAP_ARRAYS]) {}

Heap::~Heap() {
	int i;
	for (i = 0; i < heapSize; i++)
		delete[] heapArray[i].state;
	delete[] heapArray;
}

int Heap::f(Node &node) { return (node.g + node.h); }
int Heap::parent(int index) { return (index - 1) / 2; }
int Heap::left(int index) { return (index * 2) + 1; }
int Heap::right(int index) { return (index * 2) + 2; }

void Heap::insert(int state[], int g, int h) {
	int i, j;
	for (i = 0; i < MAX_PANCAKES; i++) heapArray[heapSize].state[i] = state[i];
	heapArray[heapSize].g = g; heapArray[heapSize].h = h;

	bool needSwap;
	i = heapSize;
	
	while (i != 0 && f(heapArray[parent(i)]) >= f(heapArray[i])) {
		needSwap = true;

		if (f(heapArray[parent(i)]) == f(heapArray[i])) {
			for (j = 0; j < MAX_PANCAKES; j++) { 
				if (heapArray[parent(i)].state[j] < heapArray[i].state[j]) { needSwap = false; break; }
				else if (heapArray[parent(i)].state[j] > heapArray[i].state[j]) break;
			}
		}

		if (needSwap) {
			swapNode(&heapArray[parent(i)], &heapArray[i]);
			i = parent(i);
		}
		else break;
	}

	heapSize++;
}

Node Heap::getTop() {
	if (heapSize == 1) {
		heapSize--;
		return heapArray[0];
	}

	Node root = heapArray[0];
	heapArray[0] = heapArray[heapSize - 1];
	heapSize--;
	minHeapify(0);
	
	return root;
}

void Heap::minHeapify(int index) {
	int l = left(index),
		r = right(index),
		smallest = index,
		i;

	if (l < heapSize && f(heapArray[l]) < f(heapArray[index])) smallest = l;
	else if (l < heapSize && f(heapArray[l]) == f(heapArray[index]))
		for (i = 0; i < MAX_PANCAKES; i++) {
			if (heapArray[l].state[i] < heapArray[index].state[i]) { smallest = l; break; }
			else if (heapArray[l].state[i] > heapArray[index].state[i]) break;
		}

	if (r < heapSize && f(heapArray[r]) < f(heapArray[smallest])) smallest = r;
	else if (r < heapSize && f(heapArray[r]) == f(heapArray[smallest]))
		for (i = 0; i < MAX_PANCAKES; i++) {
			if (heapArray[r].state[i] < heapArray[smallest].state[i]) { smallest = r; break; }
			else if (heapArray[r].state[i] > heapArray[smallest].state[i]) break;
		}

	if (smallest != index) {
		swapNode(&heapArray[index], &heapArray[smallest]);
		minHeapify(smallest);
	}
}

bool Heap::isEmpty() {
	return (heapSize == 0 ? true : false);
}


int main() {
	Heap priorityQueue;
	Node node;
	string cmd;
	int state[MAX_PANCAKES],
		g, h,
		i;
	
	while (getline(cin, cmd)) {

		if (!cmd.compare("INSERT")) {
			for (i = 0; i < MAX_PANCAKES; i++) cin >> state[i];
			cin >> g >> h;
			priorityQueue.insert(state, g, h);
		}

		else if (!cmd.compare("GETTOP")) {
			node = priorityQueue.getTop();

			cout << '[';
			for (i = 0; i < MAX_PANCAKES; i++) {
				if (i == MAX_PANCAKES - 1)	cout << node.state[i];
				else cout << node.state[i] << ' ';
			}
			cout << ']';
			cout << ", " << node.g << ", " << node.h << ", " << node.g + node.h << endl;
		}

		else if (!cmd.compare("GETALL")) {
			while (!priorityQueue.isEmpty()) {
				node = priorityQueue.getTop();

				cout << '[';
				for (i = 0; i < MAX_PANCAKES; i++) {
					if (i == MAX_PANCAKES - 1)	cout << node.state[i];
					else cout << node.state[i] << ' ';
				}
				cout << ']';
				cout << ", " << node.g << ", " << node.h << ", " << node.g + node.h << endl;
			}
		}
	}

	return 0;
}