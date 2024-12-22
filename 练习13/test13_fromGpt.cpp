#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

// 定义树节点结构
struct TreeNode {
	char value;
	TreeNode* left;
	TreeNode* right;
	TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

// 比较运算符优先级
int getPrecedence(char op) {
	if(op == '*' || op == '/') {
		return 2;
	} else if(op == '+' || op == '-') {
		return 1;
	}
	return 0;
}

// 生成子树并压入操作数栈
void generateSubtree(stack<TreeNode*>& operands, stack<char>& operators) {
	if(operators.empty() || operands.size() < 2) {
		cerr << "错误: 表达式无效或运算符栈状态异常。" << endl;
		exit(1);
	}
	char op = operators.top();
	operators.pop();
	TreeNode* node = new TreeNode(op);
	
	// 右子节点
	TreeNode* right = operands.top();
	operands.pop();
	
	// 左子节点
	TreeNode* left = operands.top();
	operands.pop();
	
	node->left = left;
	node->right = right;
	
	// 将新子树压回操作数栈
	operands.push(node);
}

// 打印二叉树的函数，横向打印
void printTree(TreeNode* root, int level = 0) {
	if(root == nullptr) {
		return;
	}
	
	// 先打印右子树
	printTree(root->right, level + 1);
	
	// 打印当前节点，缩进根据层级
	for(int i = 0; i < level; ++i) {
		cout << "    "; // 每层缩进4个空格
	}
	cout << root->value << endl;
	
	// 打印左子树
	printTree(root->left, level + 1);
}

int main() {
	// 打开输入文件
	ifstream inFile("input.txt");
	if(!inFile) {
		cerr << "错误: 无法打开输入文件 input.txt。" << endl;
		return 1;
	}
	
	string expression;
	// 读取整个表达式，可以包含空格
	getline(inFile, expression);
	inFile.close();
	
	stack<TreeNode*> operands;    // 操作数栈
	stack<char> operators;        // 运算符栈
	
	for(char ch : expression) {
		if(isspace(ch)) {
			continue; // 忽略空格
		}
		
		if(isalnum(ch)) {
			// 操作数直接压入操作数栈
			operands.push(new TreeNode(ch));
		}
		else if(ch == '(') {
			// 左括号压入运算符栈
			operators.push(ch);
		}
		else if(ch == ')') {
			// 处理括号内的表达式
			while(!operators.empty() && operators.top() != '(') {
				generateSubtree(operands, operators);
			}
			if(!operators.empty() && operators.top() == '(') {
				operators.pop(); // 弹出左括号
			}
			else {
				cerr << "错误: 括号不匹配。" << endl;
				return 1;
			}
		}
		else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			// 根据运算符优先级处理运算符栈
			while(!operators.empty() && operators.top() != '(' &&
				getPrecedence(operators.top()) >= getPrecedence(ch)) {
				generateSubtree(operands, operators);
			}
			operators.push(ch);
		}
		else {
			cerr << "错误: 遇到无效字符 '" << ch << "'。" << endl;
			return 1;
		}
	}
	
	// 处理剩余的运算符
	while(!operators.empty()) {
		if(operators.top() == '(' || operators.top() == ')') {
			cerr << "错误: 括号不匹配。" << endl;
			return 1;
		}
		generateSubtree(operands, operators);
	}
	
	// 最终操作数栈应只剩下一个元素，即根节点
	if(operands.size() != 1) {
		cerr << "错误: 无效的表达式。" << endl;
		return 1;
	}
	
	TreeNode* root = operands.top();
	
	// 打印表达式树
	cout << "――――――――――――――――――――" << endl;
	printTree(root);
	cout << "―――――――――――――――――――――" << endl;
	
	// 可选：释放内存（此处省略）
	return 0;
}

