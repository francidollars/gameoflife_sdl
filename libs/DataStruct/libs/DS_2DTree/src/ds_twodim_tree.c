/**
 * ds_twodim_tree.c
 *
 *  Created on: Jan 7, 2020
 *      Author: Mickey
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "DS_2DTree/ds_twodim_tree.h"

struct DS_2DNode {
	int x, y;
	struct DS_2DNode* left;
	struct DS_2DNode* right;
} Node;

static void twodim_node_init(struct DS_2DNode*, struct DS_2DNode*, struct DS_2DNode*, int, int);
static struct DS_2DNode* twodim_tree_add_node_rec(struct DS_2DNode*, int, int, int);
static struct DS_2DNode* twodim_tree_rem_node_rec(struct DS_2DNode*, int, int, int);
static struct DS_2DNode* min_node(struct DS_2DNode*, struct DS_2DNode*, struct DS_2DNode*, int);
static struct DS_2DNode* find_min_rec(struct DS_2DNode*, int, int);
static struct DS_2DNode* find_min(struct DS_2DNode*, int);

// A method to create a node of K D tree
struct DS_2DNode* twodim_tree_ctor(int _x, int _y) {
	struct DS_2DNode* root_node = malloc(sizeof(struct DS_2DNode));

	twodim_node_init(root_node, NULL, NULL, _x, _y);

	return root_node;
}

// Function to delete a given point from K D Tree with 'root'
void twodim_tree_dtor(struct DS_2DNode* _root_node) {
	// TODO: Check if root exists
    // del_node_rec(_root_node, _root_node->x, _root_node->y, 0);

}

struct DS_2DNode* twodim_tree_get_cpydatastruct(struct DS_2DNode* _root_node) {
	if (_root_node == NULL)
		return NULL;

	struct DS_2DNode* newNode = twodim_tree_ctor(_root_node->x, _root_node->y);
	newNode->left = twodim_tree_get_cpydatastruct(_root_node->left);
	newNode->right = twodim_tree_get_cpydatastruct(_root_node->right);

	return newNode;
}

struct DS_2DNode* twodim_tree_get_node(struct DS_2DNode* _node, int _x, int _y) {
	int depth = 0;

	while (_node && _node->x != _x && _node->y != _y) {
		if (!(depth++ % 2)) {
			if (_x < _node->x)
				_node = _node->left;
		} else {
			if (_y < _node->y)
				_node = _node->left;
		}

		_node = _node->right;
	}

	return _node;
}

void twodim_tree_add_node(struct DS_2DNode* _node, int _x, int _y) {
	twodim_tree_add_node_rec(_node, _x, _y, 0);

}

void twodim_tree_rem_node(struct DS_2DNode* _node, int _x, int _y) {
	twodim_tree_rem_node_rec(_node, _x, _y, 0);

}

/* const struct datastruct_vtable_* DS_TDTREE = &(struct datastruct_vtable_) {
    .ds_ctor = (struct DS_2DNode* (*)(va_list*)) twodim_tree_ctor,
    .ds_dtor = (void (*)(struct DS_2DNode*)) twodim_tree_dtor,
    .ds_get_cpydata = (struct DS_2DNode* (*)(struct DS_2DNode*)) twodim_tree_get_cpydatastruct,
    .ds_get_element = (struct DS_2DNode* (*)(struct DS_2DNode*, va_list*)) twodim_tree_get_node,
    .ds_add_element = (void (*)(struct DS_2DNode*, va_list*)) twodim_tree_add_node,
    .ds_rem_element = (void (*)(struct DS_2DNode*, va_list*)) twodim_tree_rem_node
}; */

static void twodim_node_init(struct DS_2DNode* _root_node, struct DS_2DNode* _left_node, struct DS_2DNode* _right_node, int _x, int _y) {
	_root_node->x = _x;
	_root_node->y = _y;
	_root_node->left = _left_node;
	_root_node->right = _right_node;

}

static struct DS_2DNode* twodim_tree_add_node_rec(struct DS_2DNode* _node, int _x, int _y, int depth) {
	if (_node == NULL)
		return twodim_node_ctor(_x, _y);
	else if (_x == _node->x && _y == _node->y)
		return _node;

	if ((depth++ % 2) ? (_y < _node->y) : (_x < _node->x))
		_node->left = twodim_tree_add_node_rec(_node->left, _x, _y, depth);
	else
		_node->right = twodim_tree_add_node_rec(_node->right, _x, _y, depth);

	return _node;
}

/* static struct DS_2DNode* deleteNodeRec(struct DS_2DNode* root, int _x, int _y, int depth) {
    // Given point is not present
    if (root == NULL)
        return NULL;

    // Find dimension of current node
    int cd = depth % 2;

    // If the point to be deleted is present at root
	if (_x == root->x && _y == root->y) {
        // 2.b) If right child is not NULL
        if (root->right != NULL) {
            // Find minimum of root's dimension in right subtree
            struct DS_2DNode* min = findMin(root->right, cd);

			// Copy the minimum to root
			root->x = min->x;
			root->y = min->y;

            // Recursively delete the minimum
            root->right = deleteNodeRec(root->right, min->x, min->y, depth + 1);
        } else if (root->left != NULL) { // same as above
            struct DS_2DNode* min = findMin(root->left, cd);

			// Copy the minimum to root
			root->x = min->x;
			root->y = min->y;

            root->right = deleteNodeRec(root->left, min->x, min->y, depth+1);
        } else { // If node to be deleted is leaf node
            free(root);
            return NULL;
        }

        return root;
    }

    // 2) If current node doesn't contain point, search downward
    if (point[cd] < root->point[cd])
        root->left = deleteNodeRec(root->left, point, depth+1);
    else
        root->right = deleteNodeRec(root->right, point, depth+1);
    return root;
} */

static struct DS_2DNode* twodim_tree_rem_node_rec(struct DS_2DNode* _node, int _x, int _y, int depth) {
	if (_node == NULL)
		return NULL;

	int cd = depth % 2;

	// If the point to be deleted is present at root
	if (_x == _node->x && _y == _node->y) {
		// 2.b) If right child is not NULL
		if (_node->right != NULL) {
			// Find minimum of root's dimension in right subtree
			struct DS_2DNode* min_node = find_min(_node->right, cd);

			// Copy the minimum to root
			_node->x = min_node->x;
			_node->y = min_node->y;

			// Recursively delete the minimum
			_node->right = twodim_tree_rem_node_rec(_node->right, min_node->x, min_node->y, cd + 1);
		} else if (_node->left != NULL) { // same as above
			struct DS_2DNode* min_node = find_min(_node->left, cd);

			_node->x = min_node->x;
			_node->y = min_node->y;

			_node->right = twodim_tree_rem_node_rec(_node->left, min_node->x, min_node->y, cd + 1);
			_node->left = NULL;
		} else { // If node to be deleted is leaf node
			// free(_node);

			_node = NULL;
		}

	} else if (cd ? (_y < _node->y) : (_x < _node->x)) {
		_node->left = twodim_tree_rem_node_rec(_node->left, _x, _y, cd + 1);

	} else {
		_node->right = twodim_tree_rem_node_rec(_node->right, _x, _y, cd + 1);

	}

	return _node;
}

/* static int min(int x, int y, int z) {
	int min = x;

	if (y < min)
		min = y;
	if (z < min)
		min = z;

	return min;
} */

// A utility function to find minimum of three integers
struct DS_2DNode* min_node(struct DS_2DNode* node1, struct DS_2DNode* node2, struct DS_2DNode* node3, int depth) {
	struct DS_2DNode* res = node1;

	if (node2 != NULL)
		if (res == NULL || ((depth % 2) ? (node2->y < res->y) : (node2->x < res->x)))
			res = node2;
	if (node3 != NULL)
		if (res == NULL || ((depth % 2) ? (node3->y < res->y) : (node3->x < res->x)))
			res = node3;

	return res;
}

/* static int findMinRec(struct DS_2DNode* root, int d, unsigned depth) {
	if (root == NULL)
		return INT_MAX;

	unsigned char cd = depth % 2;

	// Compare point with root with respect to cd (Current dimension)
    if (cd == d) {
        if (root->left == NULL)
            return (d ? root->y : root->x);

		int min1 = (d ? root->y : root->x);
		int min2 = findMinRec(root->left, d, depth + 1);

        return (min1 < min2) ? min1 : min2;
    }

    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return min((d ? root->y : root->x),
               findMinRec(root->left, d, depth + 1),
               findMinRec(root->right, d, depth + 1));
} */

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
struct DS_2DNode* find_min_rec(struct DS_2DNode* root, int dim, int depth) {
	// Base cases
	if (root == NULL)
		return NULL;

	int cd = depth % 2;

	if (cd == dim) {
		if (root->left == NULL) {

			return root;
		}

		return find_min_rec(root->left, dim, depth + 1);
	}

	// If current dimension is different then minimum can be anywhere
	// in this subtree
	return min_node(root, find_min_rec(root->left, dim, depth + 1), find_min_rec(root->right, dim, depth + 1), dim);
}

/* int findMin(struct DS_2DNode* root, int d) {

	return findMinRec(root, d, 0);
} */

/*
 * Wrapper over find_min_rec().
 *
 * @param root - root nod of tree
 * @return minimum of d'th dimension
 */
struct DS_2DNode* find_min(struct DS_2DNode* root, int dim) {
	// Pass current level or depth as 0
	return find_min_rec(root, dim, 0);
}

/**
 * Count the nodes surrounding the interval (x, y).
 *
 * @param   root-
 *          x-
 *          y-
 *          max_x-
 *          max_y-
 * @return  count-
 *
int count_nodes(Node* root, int x, int y, int max_x, int max_y) {
    int count = 0;
    int addx = (x + 1), subx = (x - 1);
    int addy = (y + 1), suby = (y - 1);

    if (max_x < (x + 1)) {
        addx = 0;
    } else if (x < 1) {
        subx = (max_x - 1);
    }
    if (y > max_y) {
        addy = 0;
    } else if (y < 1) {
        suby = (max_y - 1);
    }

    printf("addx: %d\n", addx);
    printf("subx: %d\n", subx);
    printf("addy: %d\n", addy);
    printf("suby: %d\n", suby);

    if (search_node(root, addx, y)) {
        count++;
    }
    if (search_node(root, x, addy)) {
        count++;
    }
    if (search_node(root, subx, y)) {
        count++;
    }
    if (search_node(root, x, suby)) {
        count++;
    }
    if (search_node(root, subx, suby)) {
        count++;
    }
    if (search_node(root, addx, addy)) {
        count++;
    }

    return count;
} */

void print_tree_rec(struct DS_2DNode* root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 5;

    // Process right child first
    print_tree_rec(root->right, space);

    // Print current node after space
    for (int i = 5; i < space; i++)
        printf(" ");

    printf("(%d, %d)\n", root->x, root->y);

    // Process left child
    print_tree_rec(root->left, space);

}

// Wrapper over print_tree_rec()
void print_tree(struct DS_2DNode* root) {
   // Pass initial space count as 0
   print_tree_rec(root, 0);

}
