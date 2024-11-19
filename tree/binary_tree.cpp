#include <iostream>
#include <vector>
#include <random>
#include <stack>

using namespace std;

class BinaryTree {
private:
	struct TreeNode {
		int key;
		TreeNode* left;
		TreeNode* right;
		
		TreeNode(int value) : 
		key(value),
		left(nullptr),
		right(nullptr) {}
	};
	int size = 1;
	TreeNode* root;
	
	TreeNode* insert(TreeNode* root, int value,int dir) {
		if (root == nullptr) 
			return new TreeNode(value);	
		if (dir % 2 == 0) {
			root->left = insert(root->left, value, rand());
		} else {
			root->right = insert(root->right, value, rand());
		}
		return root;
	}
	
	void visit(TreeNode* node) {
		cout << node->key << " ";
	}
	
	void in_order(TreeNode* root) {
		if (root == nullptr) 
			return;
		in_order(root->left);
		visit(root);
		in_order(root->right);
	}
	
	void in_order_stack(TreeNode* node) {
		stack<TreeNode*> stk;
		
		while (!stk.empty() || node) {
			while (node) {
				stk.push(node);
				node = node->left;
			}
			
			if (!stk.empty()) {
				node = stk.top();
				stk.pop();
				
				visit(node);
				
				node = node->right;
			}
		}
	}
	
	void pre_order(TreeNode* root) {
		if (root == nullptr) {
			return;
		}
		visit(root);
		pre_order(root->left);
		pre_order(root->right);
	}
	
	void pre_order_stack(TreeNode* node) {
		stack<TreeNode*> stk;
		
		while (!stk.empty() || node) {
			
			while (node) {
				stk.push(node);
				
				visit(node);
				
				node = node->left;
			}
			
			if (!stk.empty()) {
				node = stk.top();
				stk.pop();
				node = node->right;
			}
		}
	}
	
	void post_order(TreeNode* root) {
		if (root == nullptr)
			return;
		post_order(root->left);
		post_order(root->right);
		visit(root);
	}
	
	// 主要是要分清楚什么时候该出栈，什么时候该入栈。
	void post_order_stack(TreeNode* node) {
		stack<TreeNode*> stk;
		TreeNode* pre = nullptr;
		
		while (node || !stk.empty()) {
			while (node != nullptr) {
				stk.push(node);
				node = node->left;
			} 
			
			if (!stk.empty()) {
				node = stk.top();
				// 如果节点右孩子不为空并且右孩子没有被遍历过则将该节点入栈
				if (node->right && node->right != pre) {
					node = node->right;
					stk.push(node);
					node = node->left;
				} else {
					// 如果节点右孩子为空或者被遍历过，则需要将该元素出栈
					stk.pop();
					visit(node);
					pre = node;
					node = nullptr;
				}
			}
		}
	}
	
	TreeNode* find_node(TreeNode* root, int value) {
		if (root == nullptr) 
			return nullptr;
		if (root->key == value)
			return root;
		TreeNode* lresult = find_node(root->left, value);
		TreeNode* rresult = find_node(root->right, value);
		return (lresult == nullptr)? rresult : lresult;
	}

public:
	
	BinaryTree(int value) {
		root = new TreeNode(value);
	}
	
	int get_size() {
		return size;
	}
	
	bool insert(int value, int dir) {
		if (find_node(root, value) == nullptr) {
			insert(root, value, dir);
			size++;
			return true;
		}
		return false;
	}
	
	bool insert(int parent_value, int value, int dir) {
		TreeNode* parent = find_node(root, parent_value);
		if (parent == nullptr) {
			return false;
		}
		if (dir == 0) {
			if (parent->left != nullptr) {
				return false;
			} else {
				parent->left = new TreeNode(value);
				return true;
			}
		} else {
			if (parent->right != nullptr) {
				return false;
			} else {
				parent->right = new TreeNode(value);
				return true;
			}
		}
	}
	
	void in_order() {
		in_order(root);
		cout << endl;
	}
	
	void in_order_stack() {
		in_order_stack(root);
		cout << endl;
	}
	
	void pre_order() {
		pre_order(root);
		cout << endl;
	}
	
	void pre_order_stack() {
		pre_order_stack(root);
		cout << endl;
	}
	
	void post_order() {
		post_order(root);
		cout << endl;
	}
	
	void post_order_stack() {
		post_order_stack(root);
		cout << endl;
	}
};

BinaryTree* build_example() {
	BinaryTree* tree = new BinaryTree(1);
	tree->insert(1,2,0);
	tree->insert(1,3,1);
	
	tree->insert(2,4,0);
	
	tree->insert(3,7,0);
	tree->insert(3,8,1);
	
	tree->insert(4,5,1);
	
	tree->insert(5,6,0);
	
	return tree;
}


int main() {
	srand(time(0));
//	BinaryTree* tree = new BinaryTree(1);
	
//	for (int i = 0; i < 10; i++) {
//		tree->insert(rand()%20, rand()%2);
//	}
	
	BinaryTree* tree = build_example();
	
	printf("the tree size is %d\n", tree->get_size());
	
	tree->in_order();
	tree->in_order_stack();
	
	tree->pre_order();
	tree->pre_order_stack();
	
	tree->post_order();
	tree->post_order_stack();
	
	return 0;
}
