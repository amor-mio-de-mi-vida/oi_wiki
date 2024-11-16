#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <memory>

using namespace std;

enum color_t {BLACK, RED};
#define LEFT 0
#define RIGHT 1
#define left child[LEFT]
#define right child[RIGHT]
#define childDir(N) (N == (N->parent)->right? RIGHT :LEFT )

class RBtree {
private:
	struct Node {
		int key;
		color_t color;
		Node* child[2];
		Node* parent;
		
		Node(int key) {
			key = key;
			color = RED;
			left = NULL;
			right = NULL;
			parent = NULL;
		}
		
		Node* grand() {
			if (parent == NULL) 
				return NULL;
			return parent->parent;
		}
		
		Node* uncle() {
			if (grand() == NULL || parent == NULL) 
				return NULL;
			return grand()->child[parent == grand()->left? RIGHT : LEFT];
		}
		
		Node* sibling() {
			if (parent == NULL) 
				return NULL;
			return parent->child[this == parent->left? RIGHT : LEFT];
		}
	};
	
	Node* root;
	
	// 左旋指将其变为其右子节点的左子节点， 右旋是将其变为左子节点的右子节点
	Node* rotate(Node* P, int dir) {
		Node* G = P->parent;
		Node* S = P->child[1-dir];
		Node* C;
		assert(S != NULL);
		
		C = S->child[dir];
		P->child[1-dir] = C; if (C != NULL) C->parent = P;
		S->child[dir] = P; P->parent = S;
		S->parent = G;
		
		if (G != NULL)
			G->child[P == G->right ? RIGHT : LEFT] = S;
		else
			root = S;
		return S;
	}
	
	// N cannot be NULL
	Node* search(int key, Node* node) {
		if (node == NULL) 
			return NULL;
		if (key <= node->key) {
			if (node->right != NULL)
				return search(key, node->right);
			else 
				return node;
		} else {
			if (node->left != NULL)
				return search(key, node->left);
			else
				return node;
		}
	}
	
	// N cannot be NULL
	void insert_node(Node* N) {
		if (N == NULL) 
			return;
		Node* P = search(N->key, root);
		int dir;
		
		if (P == NULL)
			dir = LEFT;
		else 
			dir = (N->key < P->key) ? LEFT : RIGHT;
			
		insert_node(N, P, dir);
	}
	
	void insert_node(Node* N, Node* P, int dir) {
		Node* G;
		Node* U;
		
		N->parent = P;
		if (P == NULL) { 
			root = N;
			return;
		}
		
		P->child[dir] = N;
		
		do {
			if (P->color == BLACK) 
				return;
			
			// P is red
			if ((G = P->parent) == NULL) {
				P->color = BLACK;
				return;
			}
			
			int Pdir = childDir(P);
			U = G->child[1-Pdir];
			
			if (U == NULL || U->color == BLACK) {
				if (N == P->child[1-Pdir]) {
					rotate(P, Pdir);
					N = P;
					P = G->child[Pdir];
				}
				rotate(G, 1-Pdir);
				P->color = BLACK;
				G->color = RED;
				return;
			} else {
				P->color = BLACK;
				U->color = BLACK;
				G->color = RED;
				N = G;
			}
		} while ((P = N->parent) != NULL);
		
		return;
	}

	// Removal of a blak non-root leaf; N has no children
	void delete_leaf(Node* N) {
		Node* P = N->parent;
		int dir = childDir(N);
		Node* S;
		Node* C;
		Node* D;
		
		P->child[dir] = NULL;
		
		do {
			dir = childDir(N);
			S = P->child[1-dir];
			D = S->child[1-dir];
			C = S->child[dir];
			
			if (S->color == RED) {
				// S is red	
				rotate(P, dir);
				P->color = RED;
				S->color = BLACK;
				S = C;
				D = S->child[1-dir];
			}
			
			// S is black
			if ((D != NULL && D->color == RED) || (C != NULL && C->color == RED)) {
				// at least one nephew is red.
				if (C != NULL && C->color == RED) {
					rotate(S, 1-dir);
					S->color = RED;
					C->color = BLACK;
					D = S;
					S = C;
				}
				rotate(P,dir);
				S->color = P->color;
				P->color = BLACK;
				D->color = BLACK;
				return;
			}
			
			// both nephews are black or NULL and P is RED
			if (P->color == RED) {
				S->color = RED;
				P->color = BLACK;
				return;
			}
			
			// both nephews are black or NULL and P is BLACK
			S->color = RED;
			N = P;
		} while ((P = N->parent) != NULL);
		
		return;
	}
	
	void delete_node(Node* node) {
		if (node == NULL) 
			return;
		if (node->left && node->right) {
			// node has two children
			Node* succ = successor(node);
			node->key = succ->key;
			delete_node(succ);
		} else if (node->left || node->right) {
			// node has only one child
			if (node->parent == NULL) {
				Node* S = node->left == NULL ? node->right : node->left;
				root = S;
				S->parent = NULL;
				S->color = BLACK;
				
				free(node);
			} else {
				Node* P = node->parent;
				Node* S = node->left == NULL ? node->right : node->left;
				S->color = BLACK;
				P->child[childDir(node)] = S;
				S->parent = P;
				
				free(node);
			}
		} else {
			// node has no children
			if (node->parent == NULL) {
				root = NULL;
				free(node);
			} else 
				delete_leaf(node);
		}
	}
	
	Node* successor(Node* node) {
		if (node == NULL || node->right == NULL) {
			return NULL;
		}
		Node* result = node->right;
		while(result->left != NULL) {
			result = result->left;
		}
		return result;
	}
	
public:
	
	void insert_node(int key) {
		Node* node = new Node(key);
		insert_node(node);
	}
	
	Node* find(int key) {
		Node* result = search(key, root);
		if (result->key == key) 
			return result;
		else 
			return NULL;
	}
	
	void delete_node(int key) {
		delete_node(find(key));
	}
};



