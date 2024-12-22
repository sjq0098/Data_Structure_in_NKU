#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 定义树的节点结构
struct AVLNode {
	int val;
	AVLNode* left;
	AVLNode* right;
	AVLNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int operationCount = 0; // 用于记录操作数

// 随机化求AVL树高度的函数
int calculateAVLHeightRandomized(AVLNode* node, double checkProbability = 0.3) {
	if (!node) return 0;
	
	operationCount++; // 记录每次操作
	
	// 随机决定先计算左子树还是右子树
	AVLNode* primarySubtree;
	AVLNode* secondarySubtree;
	if (rand() % 2 == 0) {
		primarySubtree = node->left;
		secondarySubtree = node->right;
	} else {
		primarySubtree = node->right;
		secondarySubtree = node->left;
	}
	
	// 计算主要子树高度
	int primaryHeight = calculateAVLHeightRandomized(primarySubtree, checkProbability);
	
	// 在一定概率下检查次要子树高度
	if ((double)rand() / RAND_MAX < checkProbability) {
		int secondaryHeight = calculateAVLHeightRandomized(secondarySubtree, checkProbability);
		
		// 返回主要和次要子树高度的较大值 + 1
		return max(primaryHeight, secondaryHeight) + 1;
	} else {
		// 大部分情况下直接返回主要子树高度 + 1
		return primaryHeight + 1;
	}
}

class AVLTree {
public:
	AVLNode* root = nullptr;
	
	// 插入节点的辅助函数
	AVLNode* insertHelper(AVLNode* node, int val) {
		if (!node) return new AVLNode(val);
		
		if (val < node->val)
			node->left = insertHelper(node->left, val);
		else if (val > node->val)
			node->right = insertHelper(node->right, val);
		
		return node;
	}
	
	void insert(int val) {
		root = insertHelper(root, val);
	}
	
	// 中序遍历打印
	void inOrderPrint(AVLNode* node) {
		if (!node) return;
		inOrderPrint(node->left);
		cout << node->val << " ";
		inOrderPrint(node->right);
	}
};

int main() {
	srand(time(0)); // 初始化随机种子
	
	AVLTree tree;
	tree.insert(50);
	tree.insert(30);
	tree.insert(70);
	tree.insert(20);
	tree.insert(40);
	tree.insert(60);
	tree.insert(80);
	tree.insert(10);
	tree.insert(25);
	tree.insert(35);
	tree.insert(55);
	tree.insert(65);
	tree.insert(85);
	tree.insert(45);
	tree.insert(66);
	tree.insert(90);
	
	operationCount = 0; // 重置操作计数器
	int height = calculateAVLHeightRandomized(tree.root);
	
	cout << "树的高度: " << height << endl;
	cout << "操作数O: " << operationCount << endl;
	
	cout << "中序遍历: ";
	tree.inOrderPrint(tree.root);
	cout << endl;
	
	return 0;
}
