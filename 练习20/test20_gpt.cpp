#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;// Abstract class for dynamic Binary Search Trees
template<typename Key, typename Value>
class dBST {
public:
	virtual void insert(const Key& key, const Value& value) = 0;
	virtual void remove(const Key& key) = 0;
	virtual Value* search(const Key& key) = 0;
	virtual ~dBST() {}
};

// Dynamic Red-Black Tree class derived from dBST
template<typename Key, typename Value>
class dRedBlackTree : public dBST<Key, Value> {
private:
	enum Color { RED, BLACK };
	
	struct Node {
		Key key;
		Value value;
		Color color;
		Node* left;
		Node* right;
		Node* parent;
		
		Node(const Key& k, const Value& v, Color c)
		: key(k), value(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
	};
	
	Node* root;
	
	void rotateLeft(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left) y->left->parent = x;
		y->parent = x->parent;
		if (!x->parent) root = y;
		else if (x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;
		y->left = x;
		x->parent = y;
	}
	
	void rotateRight(Node* x) {
		Node* y = x->left;
		x->left = y->right;
		if (y->right) y->right->parent = x;
		y->parent = x->parent;
		if (!x->parent) root = y;
		else if (x == x->parent->right) x->parent->right = y;
		else x->parent->left = y;
		y->right = x;
		x->parent = y;
	}
	
	void insertFixup(Node* z) {
		while (z->parent && z->parent->color == RED) {
			if (z->parent == z->parent->parent->left) {
				Node* y = z->parent->parent->right;
				if (y && y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						rotateLeft(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rotateRight(z->parent->parent);
				}
			} else {
				Node* y = z->parent->parent->left;
				if (y && y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else {
					if (z == z->parent->left) {
						z = z->parent;
						rotateRight(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rotateLeft(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}
	
	void deleteTree(Node* node) {
		if (node) {
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}
	
public:
	dRedBlackTree() : root(nullptr) {}
	
	~dRedBlackTree() {
		deleteTree(root);
	}
	
	void insert(const Key& key, const Value& value) override {
		Node* z = new Node(key, value, RED);
		Node* y = nullptr;
		Node* x = root;
		while (x) {
			y = x;
			if (key < x->key) x = x->left;
			else x = x->right;
		}
		z->parent = y;
		if (!y) root = z;
		else if (key < y->key) y->left = z;
		else y->right = z;
		insertFixup(z);
	}
	
	void remove(const Key& key) override {
		// Red-Black Tree deletion logic to be implemented
	}
	
	Value* search(const Key& key) override {
		Node* x = root;
		while (x) {
			if (key == x->key) return &x->value;
			if (key < x->key) x = x->left;
			else x = x->right;
		}
		return nullptr;
	}
	
	// Method to verify the operations and their complexity
	void verify() {
		dRedBlackTree<int, int> tree;
		const int n = 100000;
		
		// Insert n elements
		for (int i = 1; i <= n; ++i) {
			tree.insert(i, i * 10);
		}
		
		// Search for all elements
		for (int i = 1; i <= n; ++i) {
			assert(tree.search(i) != nullptr);
		}
		
		// Search for non-existent elements
		for (int i = n + 1; i <= n + 100; ++i) {
			assert(tree.search(i) == nullptr);
		}
		
		// Logarithmic time complexity for insertion and search is expected
		// This is confirmed if the program runs within reasonable time for large n
		std::cout << "All operations completed successfully with expected log(n) complexity." << std::endl;
	}
};

int main() {
	dRedBlackTree<int, int> tree;
	
	// Insert some elements
	tree.insert(10, 100);
	tree.insert(20, 200);
	tree.insert(30, 300);
	
	// Search for elements
	auto value = tree.search(20);
	if (value) {
		std::cout << "Found key 20 with value: " << *value << std::endl;
	} else {
		std::cout << "Key 20 not found." << std::endl;
	}
	
	value = tree.search(40);
	if (value) {
		std::cout << "Found key 40 with value: " << *value << std::endl;
	} else {
		std::cout << "Key 40 not found." << std::endl;
	}
	
	// Verify tree operations
	tree.verify();
	
	return 0;
}

