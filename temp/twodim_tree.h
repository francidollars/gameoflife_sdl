/*
 * twodim_tree.h
 *
 *  Created on: Jan 7, 2020
 *      Author: Mickey
 */

#ifndef TWODIMTREE_H_
#define TWODIMTREE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// TODO Add TWODIMTREE structure with num_points (maybe unnecessary)
// A structure to represent node of kd tree
typedef struct Node {
	int point[2]; // To store k dimensional point
	struct Node *left, *right;

} Node;

Node* new_node(int x, int y);

Node* insert_node(Node *root, int x, int y);

bool search_node(Node* root, int x, int y);

Node* find_min(Node* root);

Node* del_node(Node* root, int x, int y);

int count_nodes(Node* root, int x, int y, int max_x, int max_y);

void print_tree(Node* root);

#endif /* TWODIMTREE_H_ */
