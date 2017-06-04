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
#include <vector>

using namespace std;

struct BPlusNode {
	
	int d;
	BPlusNode *first_child;
	vector<pair<int, BPlusNode*> > entries;
	bool is_leaf;
	
};


BPlusNode *new_node(int order, bool is_leaf) {
	BPlusNode *node = new BPlusNode;
	node->d = order; //node capacity is double this value
	node->is_leaf = is_leaf;
	return node;
}

bool entry_comparator(pair<int, BPlusNode*> i, pair<int, BPlusNode*> j) {
	return i.first < j.first;
}

pair<int, BPlusNode*> *insert_leaf_entry(pair<int, BPlusNode*> entry, BPlusNode *node);

pair<int, BPlusNode*> split_leaf_node(pair<int, BPlusNode*> new_entry, BPlusNode *node) {
	int order = node->d;
	int num_entries = node->entries.size();
	BPlusNode *new_leaf = new_node(order, true);
	vector<pair<int, BPlusNode*> > node_entries = node->entries;
	node_entries.push_back(new_entry);
	sort(node_entries.begin(), node_entries.end(), entry_comparator);
	vector<pair<int, BPlusNode*> > overwrite_entries;
	for (int i = 0; i < order; i++) {
		// put first d elements in node_entries into overwrite_entries
		overwrite_entries.push_back(node_entries[i]);
	}
	for (int i = order; i < num_entries+1; i++) {
		// put remaining entries into new_leaf
		insert_leaf_entry(node_entries[i], new_leaf);
	}
	
	node->entries = overwrite_entries;
	node_entries.clear();
	pair<int, BPlusNode*> copy_up_entry = new_leaf->entries[0];
	return copy_up_entry;
}

pair<int, BPlusNode*> inner_entry;

pair<int, BPlusNode*> *insert_leaf_entry(pair<int, BPlusNode*> entry, BPlusNode *node) {
	if (node->entries.size() == 2*node->d) {
		inner_entry = split_leaf_node(entry, node);
		return &inner_entry;
	} else {
		//insert entry as normal
		node->entries.push_back(entry);
		sort(node->entries.begin(), node->entries.end(), entry_comparator);
		return nullptr;
	}
}

pair<int, BPlusNode*> *insert_inner_entry(pair<int, BPlusNode*> entry, BPlusNode *node) {
	//stuff
	return nullptr;
}

int main() {
	int order;
	cin >> order;
	
	cout << "\n";
	
	BPlusNode *root = new_node(order, true);
	
	for (int i = 0; i < 2*root->d; i++) {
		pair<int, BPlusNode*> new_entry = make_pair(i, nullptr);
		insert_leaf_entry(new_entry, root);
	}
	
	cout << "d is: " << root->d;
	cout << "\n\n";
	
	cout << "number of entries: " << root->entries.size() << "\n\n";
	
	for (int i = 0; i < 2*root->d; i++) {
		cout << root->entries[i].first << " ";
	}
	cout << "\n\n";
	
	cout << "Inserting and splitting the node\n";
	pair<int, BPlusNode*> *copy_up = insert_leaf_entry(make_pair(8, nullptr), root);
	cout << "Node is split\n";
	
	for (int i = 0; i < root->entries.size(); i++) {
		cout << root->entries[i].first << " ";
	}
	cout << "\n" << copy_up->first << "\n";
	
}
