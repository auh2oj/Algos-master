//
//  BPlusTree.cpp
//  
//
//  Created by Joshua Goldwasser on 5/29/17.
//
//

#include "BPlusTree.hpp"
#include <stdio.h>
#include <array>
#include <iostream>

using namespace std;

struct BPlusEntry;

struct BPlusNode {
	
	int d;
	int num_entries;
	BPlusNode *first_child;
	pair<int, BPlusNode*> *entries;
	bool is_leaf;
	
};

//struct BPlusEntry {
//	int data;
//	BPlusNode *child;
//};

BPlusNode *new_node(int order, bool is_leaf) {
	BPlusNode *node = new BPlusNode;
	node->d = order;
	node->entries = new pair<int, BPlusNode*> [order];
	node->is_leaf = is_leaf;
	node->num_entries = 0;
	return node;
}

//BPlusEntry *new_entry(int data) {
//	BPlusEntry *entry = new BPlusEntry;
//	entry->data = data;
//}

bool entry_comparator(pair<int, BPlusNode*> i, pair<int, BPlusNode*> j) {
	return i.first < j.first;
}

pair<int, BPlusNode*> *insert_leaf_entry(pair<int, BPlusNode*> entry, BPlusNode *node) {
	if (node->num_entries == 2*node->d) {
		//stuff
		return &entry;
	} else {
		//insert entry as normal
		node->entries[node->num_entries++] = entry;
		sort(node->entries, node->entries + node->num_entries, entry_comparator);
		return nullptr;
	}
}

int main() {
	int order;
	cin >> order;
	
	cout << "\n";
	
	BPlusNode *root = new_node(order, true);
	
	for (int i = 0; i < 2*root->d; i++) {
		pair<int, BPlusNode*> new_entry = make_pair(i, nullptr);
//		root->entries[root->num_entries] = new_entry;
//		root->num_entries++;
		insert_leaf_entry(new_entry, root);
	}
	
//	sort(root->entries, root->entries + 2*root->d, entry_comparator);
	
	cout << "d is: " << root->d;
	cout << "\n\n";
	
	cout << "number of entries: " << root->num_entries;
	cout << "\n\n";
	
	for (int i = 0; i < 2*root->d; i++) {
		cout << root->entries[i].first << " ";
	}
	cout << "\n";

	
}
