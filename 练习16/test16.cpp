#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;
struct HuffmanTreeNode{
	char cha;
	int freq;
	HuffmanTreeNode* left;  // 左子树
	HuffmanTreeNode* right; // 右子树

	
	HuffmanTreeNode(char c,int f){
		cha=c;
		freq=f;
		left=nullptr;
		right=nullptr;
	}
};


unordered_map<char,int> count_freq_map(string& text){
	unordered_map<char,int> freq_map;
	for(char cha:text){
		freq_map[cha]++;
	}
	return freq_map;
}

class HuffmanTree {
public:
	vector<HuffmanTreeNode*> Tree;  
	int Size;  
	int capacity;  
	
	HuffmanTree(int num) {
		capacity = num;
		Size = 0;
	}
	
	
	
	void Treeifydown(int i) {
		int s = Size;
		while (2 * i + 1 < s) {  
			int left = 2 * i + 1;  
			int right = 2 * i + 2;
			int smallest = i;
			
			if (left < s && Tree[left]->freq < Tree[smallest]->freq) {
				smallest = left;
			}
			if (right < s && Tree[right]->freq < Tree[smallest]->freq) {
				smallest = right;
			}
			if (smallest != i) {
				swap(Tree[i], Tree[smallest]);
				i = smallest;
			} else {
				break;
			}
		}
	}
	
	
	void TreeifyUp(int i) {
		while (i > 0) {
			int parent = (i - 1) / 2; 
			if (Tree[parent]->freq > Tree[i]->freq) {
				swap(Tree[parent], Tree[i]);
				i = parent;
			} else {
				break;
			}
		}
	}
	
	void push(HuffmanTreeNode* k) {
		Tree.push_back(k);
		Size++;
		TreeifyUp(Size - 1);
	}
	
	HuffmanTreeNode* pop() {
		if (Size == 0) {
			cout << "Heap is empty!" << endl;
			return nullptr;
		}
		HuffmanTreeNode* Root = Tree[0];
		Tree[0] = Tree[Size - 1]; 
		Tree.pop_back(); 
		Size--;
		Treeifydown(0);  
		return Root;
	}
	
	
	HuffmanTreeNode* top(){
		if (Size == 0) return nullptr;
		return Tree[0];
	}
	
};



HuffmanTreeNode* BuildTree(unordered_map<char,int>freq_map){
	HuffmanTree MinHeap(freq_map.size());
	for(auto &Pair:freq_map){
		HuffmanTreeNode *temp=new HuffmanTreeNode(Pair.first,Pair.second);
		MinHeap.push(temp);
	}
	while(MinHeap.Size>1){
		HuffmanTreeNode *L=MinHeap.top();
		MinHeap.pop();
		HuffmanTreeNode*R=MinHeap.top();
		MinHeap.pop();
		HuffmanTreeNode *parent=new HuffmanTreeNode('\0',L->freq+R->freq);
		parent->left=L;
		parent->right=R;
		MinHeap.push(parent);	
	}
	return MinHeap.top();
}

void GenerateCode(HuffmanTreeNode* Root, string &str, unordered_map<char, string> &codes){
	if(!Root){
		return;
	}
	if(Root->cha != '\0'){
		codes[Root->cha] = str;
	}
	
	str.push_back('0');
	GenerateCode(Root->left, str, codes);
	str.pop_back();
	
	str.push_back('1');
	GenerateCode(Root->right, str, codes);
	str.pop_back();
}


string encode(string text,unordered_map<char, string> codes){
	string code="";
	for(char ch:text){
		code+=codes[ch];
	}
	return code;
}

string decode(HuffmanTreeNode* root, string encodedText){
	string decodedText = "";
	HuffmanTreeNode* current = root;
	for (char bit : encodedText) {
		if (bit == '0') {
			current = current->left;
		} else {
			current = current->right;
		}
		if (current->left == nullptr && current->right == nullptr) { // 判断是否为叶节点
			decodedText += current->cha;
			current = root;
		}
	}
	return decodedText;
}
void encode_rate(string text,unordered_map<char, string> codes,unordered_map<char,int>freq_map){
	double tL=text.length()*8;
	double cL=0;
	for(auto Pair:freq_map){
		cL+=codes[Pair.first].length()*Pair.second;
	}
	double rate=cL/tL;
	cout<<"compress rate:"<<rate<<endl;
}

void compress(string text){
	unordered_map<char,int>freq_map=count_freq_map(text);
	
	HuffmanTreeNode*root=BuildTree(freq_map);
	
	unordered_map<char,string>codes;
	string kong="";
	GenerateCode(root, kong, codes);
	
	cout << "Huffman Codes:\n";
	for(const auto& pair : codes){
		cout << pair.first << ": " << pair.second << endl;
	}
	
	string encodeText=encode(text,codes);
	cout<<"Encoded:"<<encodeText<<endl;
	
	string decodedText = decode(root,encodeText);
	cout << "Decoded text: " << decodedText << endl;
	encode_rate(text,codes,freq_map);
}


int main(){
	string inputText = "ABBCCC";
	compress(inputText);
	
	string inputText1 = "this is an example for huffman encoding";

	compress(inputText1);
	return 0;
}
