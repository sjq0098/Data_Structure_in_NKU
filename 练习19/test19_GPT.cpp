#include <iostream>
#include <string>
using namespace std;

// 基类定义
class bsTree {
public:
	virtual void ascend() const = 0; // 按键值升序输出
	virtual bool find(int x) const = 0;
	virtual void insert(int x) = 0;
	virtual void remove(int x) = 0;
};

// 红黑树节点结构
struct RedBlackTreeNode {
	int data;
	bool color; // 红色为1，黑色为0
	RedBlackTreeNode* left;
	RedBlackTreeNode* right;
	RedBlackTreeNode* parent;
	
	RedBlackTreeNode(int d = 0, bool c = false) : data(d), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

// 红黑树类
class RedBlackTree : public bsTree {
private:
	RedBlackTreeNode* Root;
	RedBlackTreeNode* NIL; // 叶子节点（NIL节点）
	
	// 左旋
	void LeftRotate(RedBlackTreeNode* x) {
		RedBlackTreeNode* y = x->right;
		x->right = y->left;
		if (y->left != NIL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NIL) {
			Root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
	
	// 右旋
	void RightRotate(RedBlackTreeNode* y) {
		RedBlackTreeNode* x = y->left;
		y->left = x->right;
		if (x->right != NIL) {
			x->right->parent = y;
		}
		x->parent = y->parent;
		if (y->parent == NIL) {
			Root = x;
		}
		else if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = x;
		}
		x->right = y;
		y->parent = x;
	}
	
	// 插入修正
	void InsertFix(RedBlackTreeNode* z) {
		while (z->parent->color == true) { // 父节点为红色
			if (z->parent == z->parent->parent->left) {
				RedBlackTreeNode* y = z->parent->parent->right; // 叔叔节点
				if (y->color == true) { // 叔叔节点为红色
					z->parent->color = false; // 父节点变黑
					y->color = false; // 叔叔节点变黑
					z->parent->parent->color = true; // 祖父节点变红
					z = z->parent->parent;
				}
				else { // 叔叔节点为黑色
					if (z == z->parent->right) { // 当前节点是右子
						z = z->parent;
						LeftRotate(z);
					}
					z->parent->color = false; // 父节点变黑
					z->parent->parent->color = true; // 祖父节点变红
					RightRotate(z->parent->parent);
				}
			}
			else { // 对称情况
				RedBlackTreeNode* y = z->parent->parent->left; // 叔叔节点
				if (y->color == true) { // 叔叔节点为红色
					z->parent->color = false; // 父节点变黑
					y->color = false; // 叔叔节点变黑
					z->parent->parent->color = true; // 祖父节点变红
					z = z->parent->parent;
				}
				else { // 叔叔节点为黑色
					if (z == z->parent->left) { // 当前节点是左子
						z = z->parent;
						RightRotate(z);
					}
					z->parent->color = false; // 父节点变黑
					z->parent->parent->color = true; // 祖父节点变红
					LeftRotate(z->parent->parent);
				}
			}
			if (z == Root) break;
		}
		Root->color = false; // 根节点必须为黑色
	}
	
	// 查找节点
	RedBlackTreeNode* SearchTree(RedBlackTreeNode* node, int key) const {
		if (node == NIL || key == node->data)
			return node;
		if (key < node->data)
			return SearchTree(node->left, key);
		else
			return SearchTree(node->right, key);
	}
	
	// 中序遍历
	void InorderHelper(RedBlackTreeNode* node) const {
		if (node != NIL) {
			InorderHelper(node->left);
			cout << node->data << " ";
			InorderHelper(node->right);
		}
	}
	
	// 最小节点
	RedBlackTreeNode* Minimum(RedBlackTreeNode* node) const {
		while (node->left != NIL)
			node = node->left;
		return node;
	}
	
	// 删除修正
	void DeleteFix(RedBlackTreeNode* x) {
		while (x != Root && x->color == false) { // 当前节点为黑色
			if (x == x->parent->left) {
				RedBlackTreeNode* w = x->parent->right;
				if (w->color == true) { // 兄弟节点为红色
					w->color = false;
					x->parent->color = true;
					LeftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == false && w->right->color == false) { // 兄弟节点的两个子节点都是黑色
					w->color = true;
					x = x->parent;
				}
				else {
					if (w->right->color == false) { // 兄弟节点的右子节点为黑色
						w->left->color = false;
						w->color = true;
						RightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = false;
					w->right->color = false;
					LeftRotate(x->parent);
					x = Root;
				}
			}
			else { // 对称情况
				RedBlackTreeNode* w = x->parent->left;
				if (w->color == true) { // 兄弟节点为红色
					w->color = false;
					x->parent->color = true;
					RightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == false && w->left->color == false) { // 兄弟节点的两个子节点都是黑色
					w->color = true;
					x = x->parent;
				}
				else {
					if (w->left->color == false) { // 兄弟节点的左子节点为黑色
						w->right->color = false;
						w->color = true;
						LeftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = false;
					w->left->color = false;
					RightRotate(x->parent);
					x = Root;
				}
			}
		}
		x->color = false;
	}
	
	// 转换节点颜色
	void Transplant(RedBlackTreeNode* u, RedBlackTreeNode* v) {
		if (u->parent == NIL)
			Root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}
	
	// 删除节点
	void RemoveNode(RedBlackTreeNode* z) {
		RedBlackTreeNode* y = z;
		RedBlackTreeNode* x;
		bool y_original_color = y->color;
		if (z->left == NIL) {
			x = z->right;
			Transplant(z, z->right);
		}
		else if (z->right == NIL) {
			x = z->left;
			Transplant(z, z->left);
		}
		else {
			y = Minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else {
				Transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			Transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == false)
			DeleteFix(x);
	}
	
public:
	// 构造函数
	RedBlackTree() {
		NIL = new RedBlackTreeNode();
		NIL->color = false; // NIL节点为黑色
		NIL->left = NIL->right = NIL->parent = NIL;
		Root = NIL;
	}
	
	// 析构函数
	~RedBlackTree() {
		// 使用后序遍历删除所有节点
		destroyTree(Root);
		delete NIL;
	}
	
	void destroyTree(RedBlackTreeNode* node) {
		if (node != NIL) {
			destroyTree(node->left);
			destroyTree(node->right);
			delete node;
		}
	}
	
	// 插入函数
	void insert(int data) override {
		RedBlackTreeNode* z = new RedBlackTreeNode(data);
		z->left = z->right = z->parent = NIL;
		
		RedBlackTreeNode* y = NIL;
		RedBlackTreeNode* x = Root;
		
		// 标准BST插入
		while (x != NIL) {
			y = x;
			if (z->data < x->data)
				x = x->left;
			else
				x = x->right;
		}
		
		z->parent = y;
		if (y == NIL)
			Root = z;
		else if (z->data < y->data)
			y->left = z;
		else
			y->right = z;
		
		z->color = true; // 新插入的节点为红色
		
		InsertFix(z);
	}
	
	// 查找函数
	bool find(int x) const override {
		RedBlackTreeNode* node = SearchTree(Root, x);
		return (node != NIL);
	}
	
	// 删除函数
	void remove(int data) override {
		RedBlackTreeNode* z = SearchTree(Root, data);
		if (z == NIL) {
			cout << "未找到要删除的节点: " << data << endl;
			return;
		}
		RemoveNode(z);
	}
	
	// 中序遍历
	void ascend() const override {
		InorderHelper(Root);
		cout << endl;
	}
	
	// 打印红黑树的结构（可选，用于调试）
	void PrintHelper(RedBlackTreeNode* root, string indent, bool last) const {
		if (root != NIL) {
			cout << indent;
			if (last) {
				cout << "R----";
				indent += "     ";
			}
			else {
				cout << "L----";
				indent += "|    ";
			}
			
			string sColor = root->color ? "RED" : "BLACK";
			cout << root->data << "(" << sColor << ")" << endl;
			PrintHelper(root->left, indent, false);
			PrintHelper(root->right, indent, true);
		}
	}
	
	void printTree() const {
		if (Root == NIL) {
			cout << "树是空的" << endl;
		}
		else {
			PrintHelper(Root, "", true);
		}
	}
};

// 主函数用于测试
int main() {
	RedBlackTree tree;
	int n, value;
	cout << "请输入要插入的节点数量: ";
	cin >> n;
	cout << "请输入节点的值:\n";
	for(int i = 0; i < n; ++i){
		cin >> value;
		tree.insert(value);
	}
	
	cout << "红黑树的升序输出: ";
	tree.ascend();
	
	cout << "红黑树的结构:\n";
	tree.printTree();
	
	// 测试查找
	cout << "请输入要查找的值: ";
	cin >> value;
	if(tree.find(value))
		cout << "找到值 " << value << " 在树中.\n";
	else
		cout << "未找到值 " << value << " 在树中.\n";
	
	// 测试删除
	cout << "请输入要删除的值: ";
	cin >> value;
	tree.remove(value);
	cout << "删除后红黑树的升序输出: ";
	tree.ascend();
	cout << "删除后红黑树的结构:\n";
	tree.printTree();
	
	return 0;
}

