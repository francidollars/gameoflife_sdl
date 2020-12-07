/*
 * twodim_tree.c
 * 
 *  Created on: Jan 7, 2020
 *      Author: Mickey
 */

#include "twodim_tree.h"

// Helper functions
Node* insert_rec(Node*, int[2], unsigned int);
bool points_equal(int[2], int[2]);
bool search_node_rec(Node*, int[2], unsigned int);
Node* min_node(Node*, Node*, Node*, int);
Node* find_min_rec(Node*, int, unsigned int);
void cpy_point(int[2], int[2]);
Node* del_node_rec(Node*, int[2], int);
void print_tree_rec(Node*, int);

const int k = 2;

// A method to create a node of K D tree 
Node* new_node(int x, int y) { 
	Node* temp = malloc(sizeof(Node*));

	temp->point[0] = x;
	temp->point[1] = y;

	temp->left = temp->right = NULL;

	return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node* insert_rec(Node* root, int point[2], unsigned int depth) {
    // Tree is empty
	if (root == NULL) {

	    return new_node(point[0], point[1]);
    // Tree already contains point
    } else if (points_equal(root->point, point)) {

        return root;
    }

	// Calculate current dimension (cd) of comparison
	unsigned int cd = depth % k;

	// Compare the new point with root on current dimension 'cd'
	// and decide the left or right subtree
	if (point[cd] < (root->point[cd]))
		root->left = insert_rec(root->left, point, depth + 1);
	else
		root->right = insert_rec(root->right, point, depth + 1);

	return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insert_rec()"
Node* insert_node(Node* root, int x, int y) {
    int temp_point[2] = { x , y };

	return insert_rec(root, temp_point, 0);
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool points_equal(int point1[2], int point2[2]) {
	// Compare individual pointinate values
	for (int i = 0; i < k; ++i)
		if (point1[i] != point2[i])
			return false;

	return true;
}

/**
 * Searches for a Point represented by "point[]" in the K-D tree.
 * 
 * @param   root- root node of K-D tree
 *          point- Point with (x, y)
 *          depth- used to determine current axis
 * @return  search_node_rec()- recursive call to run function again
 * 
 */
bool search_node_rec(Node* root, int point[2], unsigned depth) {
	// Base cases
	if (root == NULL)
		return false;
	if (points_equal(root->point, point))
		return true;

	// Current dimension is computed using current depth and total 
	// dimensions (k) 
	unsigned cd = depth % k;

	// Compare point with root with respect to cd (Current dimension) 
	if (point[cd] < root->point[cd])
		return search_node_rec(root->left, point, ++depth);

	return search_node_rec(root->right, point, ++depth);
}

/**
 * Wrapper over search_node_rec. Searches for a Point in K-D tree
 * 
 * @param   root- root node of K-D tree
 *          x- x coordinate of Point
 *          y- y coordinate of Point
 * @return  search_node_rec()- call to recursive funtion to search for node
 */
bool search_node(Node* root, int x, int y) {
    int temp_point[2] = { x , y };
    
	// Pass current depth as 0
	return search_node_rec(root, temp_point, 0); 
}

// A utility function to find minimum of three integers 
Node* min_node(Node* x, Node* y, Node* z, int d) { 
	Node* res = x;
    
	if (y != NULL && y->point[d] < res->point[d]) 
	res = y; 
	if (z != NULL && z->point[d] < res->point[d]) 
	res = z;

	return res;
}

// Recursively finds minimum of d'th dimension in KD tree 
// The parameter depth is used to determine current axis. 
Node* find_min_rec(Node* root, int d, unsigned int depth) {
	// Base cases 
	if (root == NULL) 
		return NULL; 

	// Current dimension is computed using current depth and total 
	// dimensions (k) 
	unsigned int cd = depth % k; 

	// Compare point with root with respect to cd (Current dimension) 
	if (cd == (unsigned int) d) {
		if (root->left == NULL)
			return root;

		return find_min_rec(root->left, d, depth + 1);
	}

	// If current dimension is different then minimum can be anywhere
	// in this subtree
	return min_node(root, 
			find_min_rec(root->left, d, depth + 1), 
			find_min_rec(root->right, d, depth + 1), d); 
} 

/**
 * Wrapper over find_min_rec().
 * 
 * @param root - root nod of tree
 * @return minimum of d'th dimension
 */
Node* find_min(Node* root) { 
	// Pass current level or depth as 0 
	return find_min_rec(root, 2, 0); 
} 

// Copies point point2 to point1
/**
 * Copies point
 * 
 * @param point1 - copied point
 * @param point2 - reciever point
 */
void cpy_point(int point1[2], int point2[2]) {
    for (int i=0; i<k; i++) 
	    point2[i] = point1[i]; 

} 

// Function to delete a given point 'point[]' from tree with root 
// as 'root'. depth is current depth and passed as 0 initially. 
// Returns root of the modified tree. 
Node* del_node_rec(Node* root, int point[2], int depth) {
	// Given point is not present 
	if (root == NULL)
		return NULL;

	// Find dimension of current node
	int cd = depth % k;

	// If the point to be deleted is present at root
	if (points_equal(root->point, point)) {
		// 2.b) If right child is not NULL
		if (root->right != NULL) {
			// Find minimum of root's dimension in right subtree
			Node* min = find_min(root->right);

			// Copy the minimum to root
			cpy_point(root->point, min->point);

			// Recursively delete the minimum
			root->right = del_node_rec(root->right, min->point, depth + 1);
		}
		else if (root->left != NULL) { // same as above
			Node* min = find_min(root->left);
			cpy_point(root->point, min->point);
			root->right = del_node_rec(root->left, min->point, depth + 1);
		} 
		else { // If node to be deleted is leaf node
			free(root);

			return NULL;
		}

		return root;
	}

	// 2) If current node doesn't contain point, search_node downward
	if (point[cd] < root->point[cd])
		root->left = del_node_rec(root->left, point, depth+1);
	else
		root->right = del_node_rec(root->right, point, depth+1);

	return root;
}

// Function to delete a given point from K D Tree with 'root' 
Node* del_node(Node* root, int x, int y) {
    if (search_node(root, x, y))
        return root;
    
    int temp_point[2] = { x , y };
    // Pass depth as 0 
    return del_node_rec(root, temp_point, 0); 
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
 */
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
}
                                              
void print_tree_rec(Node* root, int space) {
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

    printf("(%d, %d)\n", root->point[0], root->point[1]); 
  
    // Process left child 
    print_tree_rec(root->left, space);

} 
  
// Wrapper over print_tree_rec() 
void print_tree(Node* root) { 
   // Pass initial space count as 0 
   print_tree_rec(root, 0);

}

