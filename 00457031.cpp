#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include <string>
#include<vector>
using namespace std;

class node {
public:
	node(int node_number) {
		my_node_number = node_number;
	}
	~node() {}
	void set_node_string(string node) {
		node_string = node;
	}
	void set_node() {
		char temp_node[200];
		strcpy(temp_node, node_string.c_str());
		//cout << temp_node;
		char * pch;
		pch = strtok(temp_node, " ");
		int array_index= 0;
		while (pch != NULL) {
			//cout << atoi(pch)<<"\n";
			mynode[array_index] = atoi(pch);
			array_index++;
			if (array_index > 16) {
				break;
			}
			pch = strtok(NULL, " ");
		}
	}
	int get_f() {
		return my_g + my_h;
	}
	int get_per_node(int index) {
		return mynode[index];
	}

	void set_g(int g) {
		my_g = g;
	}
	void set_h(int h) {
		my_h = h;
	}
	void print_node() {
		cout << "[";
		for (int i = 0; i < my_node_number; i++) {
			if(i== my_node_number-1)
				cout << mynode[i]<<"]";
			else 
			cout << mynode[i]<<" ";
		}
		cout << ", "<< my_g;
		cout << ", " << my_h;
		cout << ", " << my_g+my_h;
		cout << "\n";
	}
	void print_g() {
		cout << "g:"<< my_g;
	}
	void print_h() {
		cout << "h:"<< my_h;
	}
private:
	// 存放一個pancake的node數
    int my_node_number ;
	//int *mynode = (int*)malloc(sizeof(int) * (my_node_number+10));
	int mynode[16];
	string node_string;
	int my_g;
	int my_h;
};

class pancake {
public:
	// 生成一pancake物件 並把index_0的值設定好
	pancake(int pancakes_node) {
		my_pancakes_node_number = pancakes_node;
		node index(pancakes_node);
		queue_node_number.push_back(index);
	}
	void put_in(node &a) {
		queue_node_number.push_back(a);
	}
	void get_all() {
		while (queue_node_number.size() != 1) {
			take_the_node();
		}
	}
	void take_the_node() {
		if (queue_node_number.size() != 1) {
			node temp_node = queue_node_number[1];

			if (queue_node_number.size() > 2)
				heapify_the_node();
			temp_node = queue_node_number[1];
			queue_node_number[1] = queue_node_number[queue_node_number.size() - 1];
			queue_node_number[queue_node_number.size() - 1] = temp_node;
			temp_node.print_node();
			queue_node_number.pop_back();

		}
	}
	void heapify_the_node() {
		int array_size = queue_node_number.size();
		for (int i = array_size-1; i >= 1; i--) {
			int temp_index = i;
			int the_next_compare_index = i/2;
			if (the_next_compare_index == 0) {
				break;	 
			}
			while (queue_node_number[temp_index].get_f() <= queue_node_number[the_next_compare_index].get_f()) {
				int swap_action = 1;
				if (queue_node_number[temp_index].get_f() == queue_node_number[the_next_compare_index].get_f()) {
					int j = 0;
					while (j < my_pancakes_node_number) {
						if (queue_node_number[temp_index].get_per_node(j) < queue_node_number[the_next_compare_index].get_per_node(j)) {
							swap_action = 1;
							break;
						}
						else if(queue_node_number[temp_index].get_per_node(j) > queue_node_number[the_next_compare_index].get_per_node(j)){
							swap_action = -1;
							break;
						}
						j = j + 1;
					}
				} 
				if(swap_action ==1){
					swap(temp_index,the_next_compare_index);
					temp_index = the_next_compare_index;
					the_next_compare_index = temp_index / 2;
					if (temp_index == 1) {
						break;
					}
				}
				if (swap_action == -1) {
					break;
				}
			}
		}
	}
	void swap(int temp_index,int the_next_compare_index) {
		node temp = queue_node_number[temp_index];
        queue_node_number[temp_index] = queue_node_number[the_next_compare_index];
		queue_node_number[the_next_compare_index] = temp;
	}
	void print_the_node() {
		int array_size = queue_node_number.size();
		for (int i = 1; i<array_size;i++) {
			queue_node_number[i].print_node();
			cout << "\n";
		}
	}
private:
	vector<node>queue_node_number;
	int my_pancakes_node_number;
};

int main() {
	pancake pancake(16);
    string input = "START";
	while (input.compare("GETALL") != 0) {
		cin >> input;
		if (input.compare("INSERT") == 0) {
			string input_data;
            node a(16);
		    cin.ignore();
			getline(cin, input_data);
			a.set_node_string(input_data);
			cin >> input_data;
			a.set_g(atoi(input_data.c_str()));		
			cin >> input_data;
			a.set_h(atoi(input_data.c_str()));
			a.set_node();
			pancake.put_in(a);
		}
		else if (input.compare("GETTOP") == 0) {
			pancake.take_the_node();
		}
	}
	pancake.get_all();
	system("pause");
}