#include<iostream>
#include<vector>
#include<stack>
#include<fstream>
#include<string>
using namespace std;

struct TreeNode {
	char value;
	TreeNode* left;
	TreeNode* right;
	TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

int compare(char a){
	if(a=='*'||a=='/'){
		return 2;
	}
	else if(a=='+'||a=='-'){
		return 1;
	}
	return 0;
}

void Generate_subtree(stack<TreeNode*>&operand,stack<char> &opertor){
	char opert=opertor.top();
	opertor.pop();
	TreeNode* Temp=new TreeNode(opert);
	TreeNode*Right=operand.top();
	operand.pop();
	TreeNode*Left=operand.top();
	operand.pop();
	Temp->left=Left;
	Temp->right=Right;
	operand.push(Temp);
}

void Print(TreeNode*Root,int level=0){
	if(Root==nullptr){
		return;
	}
	Print(Root->right,level+1);
	for(int i=0;i<level;i++){
		cout<<"   ";
	}
	cout<<Root->value<<endl;
	Print(Root->left,level+1);
	
}
int main(){
	ifstream in("input.txt");
	string x1;
	in>>x1;
	stack<TreeNode*> operand;
	stack<char>opertor;
	for(size_t i=0;i<x1.length();i++){
		char ch=x1[i];
		if(ch==' '){
			continue;
		}
		if(isalnum(ch)){
			TreeNode*Temp=new TreeNode(ch);
			operand.push(Temp);
		}
		else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
			while(!opertor.empty()&&opertor.top()!='('&&(compare(opertor.top())>=compare(ch))){
				Generate_subtree(operand,opertor);
			}
			opertor.push(ch);
		}
		else if(ch=='('){
			opertor.push(ch);
		}
		else if(ch==')'){
			while(opertor.top()!='('){
				Generate_subtree(operand,opertor);
			}
			opertor.pop();
		}
	}
	while(!opertor.empty()){
		Generate_subtree(operand,opertor);
	}
	TreeNode*Root=operand.top();
	Print(Root);
	return 0;
}
