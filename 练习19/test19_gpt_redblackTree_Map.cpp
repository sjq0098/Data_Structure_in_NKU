
#include <iostream>
#include <queue>
using namespace std;

// 抽象类 bsTree
template <class K, class E>
class bsTree {
public:
	virtual void ascend() = 0; // 按键值升序输出
	virtual E* find(const K&) const = 0;
	virtual void insert(const pair<K, E>&) = 0;
	virtual void remove(const K&) = 0;
	virtual ~bsTree() {}
};

// 红黑树节点
enum Color { RED, BLACK };

template <class K, class E>
struct TreeNode {
	pair<K, E> data;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	Color color;
	
	TreeNode(const pair<K, E>& element, Color c = RED)
	: data(element), left(nullptr), right(nullptr), parent(nullptr), color(c) {}
};

// 红黑树实现
template <class K, class E>
class redBlackTree : public bsTree<K, E> {
private:
	TreeNode<K, E>* root;
	TreeNode<K, E>* nil; // 哨兵节点
	
	// 左旋操作
	void leftRotate(TreeNode<K, E>* x) {
		TreeNode<K, E>* y = x->right;
		x->right = y->left;
		if (y->left != nil) y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}
	
	// 右旋操作
	void rightRotate(TreeNode<K, E>* x) {
		TreeNode<K, E>* y = x->left;
		x->left = y->right;
		if (y->right != nil) y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
			root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}
	
	// 插入修复
	void insertFixup(TreeNode<K, E>* z) {
		while (z->parent->color == RED) {
			if (z->parent == z->parent->parent->left) {
				TreeNode<K, E>* y = z->parent->parent->right;
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			} else {
				TreeNode<K, E>* y = z->parent->parent->left;
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else {
					if (z == z->parent->left) {
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}
	
	// 删除修复
	void deleteFixup(TreeNode<K, E>* x) {
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				TreeNode<K, E>* w = x->parent->right;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				TreeNode<K, E>* w = x->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}
	
	// 删除节点
	void deleteNode(TreeNode<K, E>* z) {
		TreeNode<K, E>* y = z;
		TreeNode<K, E>* x;
		Color yOriginalColor = y->color;
		if (z->left == nil) {
			x = z->right;
			transplant(z, z->right);
		} else if (z->right == nil) {
			x = z->left;
			transplant(z, z->left);
		} else {
			y = minimum(z->right);
			yOriginalColor = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (yOriginalColor == BLACK)
			deleteFixup(x);
	}
	
	// 辅助函数：用 v 替换 u
	void transplant(TreeNode<K, E>* u, TreeNode<K, E>* v) {
		if (u->parent == nil)
			root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}
	
	// 找到以 x 为根的最小节点
	TreeNode<K, E>* minimum(TreeNode<K, E>* x) const {
		while (x->left != nil)
			x = x->left;
		return x;
	}
	
	// 中序遍历辅助函数
	void inorder(TreeNode<K, E>* x) const {
		if (x != nil) {
			inorder(x->left);
			cout << x->data.first << ": " << x->data.second << endl;
			inorder(x->right);
		}
	}
	
public:
	// 构造函数
	redBlackTree() {
		nil = new TreeNode<K, E>(pair<K, E>(K(), E()), BLACK);
		root = nil;
	}
	
	// 查找
	E* find(const K& key) const override {
		TreeNode<K, E>* current = root;
		while (current != nil) {
			if (key == current->data.first)
				return &current->data.second;
			else if (key < current->data.first)
				current = current->left;
			else
				current = current->right;
		}
		return nullptr;
	}
	
	// 插入
	void insert(const pair<K, E>& element) override {
		TreeNode<K, E>* z = new TreeNode<K, E>(element);
		TreeNode<K, E>* y = nil;
		TreeNode<K, E>* x = root;
		while (x != nil) {
			y = x;
			if (z->data.first < x->data.first)
				x = x->left;
			else
				x = x->right;
		}
		z->parent = y;
		if (y == nil)
			root = z;
		else if (z->data.first < y->data.first)
			y->left = z;
		else
			y->right = z;
		z->left = nil;
		z->right = nil;
		z->color = RED;
		insertFixup(z);
	}
	
	// 删除
	void remove(const K& key) override {
		TreeNode<K, E>* z = root;
		while (z != nil && z->data.first != key) {
			if (key < z->data.first)
				z = z->left;
			else
				z = z->right;
		}
		if (z == nil) return; // 未找到
		deleteNode(z);
	}
	
	// 中序遍历
	void ascend() override {
		inorder(root);
	}
	
	// 析构函数
	~redBlackTree() {
		// TODO: 清理内存
	}
};

// 测试
int main() {
	redBlackTree<int, string> tree;
	tree.insert({10, "ten"});
	tree.insert({20, "twenty"});
	tree.insert({15, "fifteen"});
	tree.insert({30, "thirty"});
	
	cout << "In-order traversal:" << endl;
	tree.ascend();
	
	tree.remove(20);
	cout << "After removing 20:" << endl;
	tree.ascend();
	
	return 0;
}

