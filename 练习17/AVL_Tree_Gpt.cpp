#include <iostream>
#include <algorithm> // 用于std::max

// 定义AVL树的节点结构
struct AVLNode {
	int key;
	AVLNode* left;
	AVLNode* right;
	int height;
	
	AVLNode(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

// 获取节点高度
int getHeight(AVLNode* node) {
	if (node == nullptr)
		return 0;
	return node->height;
}

// 计算平衡因子
int getBalanceFactor(AVLNode* node) {
	if (node == nullptr)
		return 0;
	return getHeight(node->left) - getHeight(node->right);
}

// 右旋操作
AVLNode* rightRotate(AVLNode* y) {
	AVLNode* x = y->left;
	AVLNode* T2 = x->right;
	
	// 执行旋转
	x->right = y;
	y->left = T2;
	
	// 更新高度
	y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
	
	// 返回新的根节点
	return x;
}

// 左旋操作
AVLNode* leftRotate(AVLNode* x) {
	AVLNode* y = x->right;
	AVLNode* T2 = y->left;
	
	// 执行旋转
	y->left = x;
	x->right = T2;
	
	// 更新高度
	x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
	
	// 返回新的根节点
	return y;
}

// 插入节点并保持AVL树的平衡
AVLNode* insert(AVLNode* node, int key) {
	// 1. 执行普通的BST插入
	if (node == nullptr)
		return new AVLNode(key);
	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // 不允许插入重复键
		return node;
	
	// 2. 更新当前节点的高度
	node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
	
	// 3. 获取平衡因子
	int balance = getBalanceFactor(node);
	
	// 4. 如果节点不平衡，则有4种情况
	
	// 情况1：左左 (LL)
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);
	
	// 情况2：右右 (RR)
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);
	
	// 情况3：左右 (LR)
	if (balance > 1 && key > node->left->key) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	
	// 情况4：右左 (RL)
	if (balance < -1 && key < node->right->key) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	
	// 返回（未变化的）节点指针
	return node;
}

// 中序遍历打印AVL树
void inorderTraversal(AVLNode* root) {
	if (root != nullptr) {
		inorderTraversal(root->left);
		std::cout << root->key << " ";
		inorderTraversal(root->right);
	}
}

// 前序遍历打印AVL树及其高度
void preorderTraversal(AVLNode* root) {
	if (root != nullptr) {
		std::cout << root->key << "(" << root->height << ") ";
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

// 主函数示例
int main() {
	AVLNode* root = nullptr;
	
	/* 插入节点构建以下AVL树：
	   30
	   /  \
	 20    40
	/  \     \
	10   25    50
	
	*/
	
	root = insert(root, 30);
	root = insert(root, 20);
	root = insert(root, 40);
	root = insert(root, 10);
	root = insert(root, 25);
	root = insert(root, 50);
	
	// 打印中序遍历结果
	std::cout << "中序遍历AVL树: ";
	inorderTraversal(root);
	std::cout << std::endl;
	
	// 打印前序遍历结果（显示节点高度）
	std::cout << "前序遍历AVL树（显示节点高度）: ";
	preorderTraversal(root);
	std::cout << std::endl;
	
	// 计算并打印树高
	std::cout << "AVL树的高度为: " << root->height - 1 << std::endl; // 根据之前高度定义，根高度为实际高度+1
	
	// 释放内存（此处未实现，实际应用中应实现释放函数）
	return 0;
}

