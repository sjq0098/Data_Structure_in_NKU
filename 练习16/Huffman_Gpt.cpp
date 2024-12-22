#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <bitset>
#include <fstream>

using namespace std;

// 1. 定义霍夫曼树节点结构体
struct HuffmanNode {
	char data;
	int freq;
	HuffmanNode* left;
	HuffmanNode* right;
	
	HuffmanNode(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
	// 自定义比较器，用于优先队列
	bool operator>(const HuffmanNode& other) const {
		return freq > other.freq;
	}
};

// 2. 计算字符频率
unordered_map<char, int> calculateFrequency(const string& text) {
	unordered_map<char, int> freqMap;
	for (char ch : text) {
		freqMap[ch]++;
	}
	return freqMap;
}

// 3. 构建霍夫曼树
HuffmanNode* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
	priority_queue<HuffmanNode, vector<HuffmanNode>, greater<HuffmanNode>> minHeap;
	
	// 创建每个字符的霍夫曼树节点，并放入优先队列
	for (const auto& pair : freqMap) {
		minHeap.push(HuffmanNode(pair.first, pair.second));
	}
	
	// 构建霍夫曼树
	while (minHeap.size() > 1) {
		HuffmanNode* left = new HuffmanNode(minHeap.top());
		minHeap.pop();
		HuffmanNode* right = new HuffmanNode(minHeap.top());
		minHeap.pop();
		
		// 创建一个新的父节点
		HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
		parent->left = left;
		parent->right = right;
		
		minHeap.push(*parent);
	}
	
	return new HuffmanNode(minHeap.top());
}

// 4. 生成编码
void generateCodes(HuffmanNode* root, string str, unordered_map<char, string>& codes) {
	if (!root) return;
	
	if (root->data != '\0') {
		// 叶子节点，存储字符的编码
		codes[root->data] = str;
	}
	
	generateCodes(root->left, str + "0", codes);
	generateCodes(root->right, str + "1", codes);
}

// 5. 编码函数
string encode(const string& text, const unordered_map<char, string>& codes) {
	string encodedText = "";
	for (char ch : text) {
		encodedText += codes.at(ch);
	}
	return encodedText;
}

// 6. 解码函数
string decode(const string& encodedText, HuffmanNode* root) {
	string decodedText = "";
	HuffmanNode* current = root;
	for (char bit : encodedText) {
		if (bit == '0') {
			current = current->left;
		} else {
			current = current->right;
		}
		
		if (current->data != '\0') {
			decodedText += current->data;
			current = root;
		}
	}
	return decodedText;
}

// 7. 压缩（编码）
void compress(const string& text) {
	unordered_map<char, int> freqMap = calculateFrequency(text);
	
	// 构建霍夫曼树
	HuffmanNode* root = buildHuffmanTree(freqMap);
	
	// 生成霍夫曼编码表
	unordered_map<char, string> codes;
	generateCodes(root, "", codes);
	
	// 编码文本
	string encodedText = encode(text, codes);
	cout << "Encoded text: " << encodedText << endl;
	
	// 解码文本
	string decodedText = decode(encodedText, root);
	cout << "Decoded text: " << decodedText << endl;
}

int main() {
	string inputText = "this is an example for huffman encoding";
	
	// 调用压缩函数
	compress(inputText);
	
	return 0;
}

