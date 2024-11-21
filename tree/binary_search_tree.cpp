#include <iostream>


class BST{
private:
	struct TreeNode {
		int key;
		TreeNode* left;
		TreeNode* right;
		int size;
		int count;
		
		TreeNode(int value) : 
		key(value), 
		left(nullptr),
		right(nullptr),
		size(1),
		count(1) {}
	};
	TreeNode* root;
public:
	
	void inorderTraversal(TreeNode* root) {
		if (root == nullptr) 
			return;
		inorderTraversal(root->left);
		//do something;
		std::cout << root->key << " ";
		inorderTraversal(root->right);
	}
	
	int findMin(TreeNode* root) {
		if (root == nullptr) {
			return -1;
		}
		while (root->left != nullptr) {
			root = root->left;
		}
		return root->key;
	}
	
	int findMax(TreeNode* root) {
		if (root == nullptr) {
			return -1;
		}
		while (root->right != nullptr) {
			root = root->right;
		}
		return root->key;
	}
	
	bool search(TreeNode* root, int target) {
		if (root == nullptr) {
			return false;
		}
		
		if (target < root->key) 
			return search(root->left, target);
		else if (target > root->key)
			return search(root->right, target);
		else 
			return true;
	}
	
	TreeNode* insert(TreeNode* root, int value) {
		if (root == nullptr) {
			return new TreeNode(value);
		}
		if (root->key == value) {
			root->count++;
		} else if (root->key < value) {
			root->left = insert(root->left, value);
		} else {
			root->right = insert(root->right, value);
		}
		root->size = root->count + (root->left? root->left->size : 0) + 
		(root->right? root->right->size : 0);
		return root;
	}
	
	TreeNode* findMinNode(TreeNode* root) {
		if (root == nullptr) {
			return nullptr;
		} 
		while (root->left != nullptr) {
			root = root->left;
		}
		return root;
	}
	
	TreeNode* remove(TreeNode* root, int value) {
		if (root == nullptr) {
			return root;
		}
		if (value < root->key) {
			root->left = remove(root->left, value);
		} else if (value > root->key) {
			root->right = remove(root->right, value);
		} else {
			if (root->count > 1) {
				root->count--;
			} else {
				if (root->left == nullptr) {
					TreeNode* temp = root->right;
					delete root;
					return temp;
				} else if (root->right == nullptr) {
					TreeNode* temp = root->left;
					delete root;
					return temp;
				} else {
					TreeNode* successor = findMinNode(root->right);
					root->key = successor->key;
					root->count = successor->count;
					successor->count = 1;
					root->right = remove(root->right, successor->key);
				}
			}
		} 
		root->size = root->count + (root->left? root->left->size : 0) + 
			(root->right? root->right->count : 0);
		return root;
	}
	
	int queryRank(TreeNode* root, int v) {
		if (root == nullptr) return 0;
		if (root->key == v) return (root->left? root->left->count : 0);
		if (root->key > v) return queryRank(root->left);
		return queryRank(root->right, v) + (root->left ? root->left->size : 0) +
		root->count;
	}
	
	int querykth(TreeNode* root, int k) {
		if (root == nullptr) return -1;
		if (root->left) {
			if (root->left->size >= k) return querykth(root->left, k);
			if (root->left->size + root->count >= k) return root->key;
		} else {
			if (k == 1) return root->key;
		}
		return querykth(root->right, k - root->count - (root->left? root->left->count : 0));
	}
};
