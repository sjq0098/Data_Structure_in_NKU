#include <iostream>
#include <fstream>
using namespace std;

int main() {
	int n, m;
	ifstream in("input.txt");
	in >> n >> m;
	m = m % n;
	int* Jose = new int[n];
	bool* eliminated = new bool[n]();
	
	for (int i = 0; i < n; i++) {
		Jose[i] = i + 1;
	}
	
	int remaining = n;
	int index = 0;
	int count = 0;
	
	while (remaining > 0) {
		if (!eliminated[index]) {
			count++;
			if (count == m) {
				cout << Jose[index] << " ";
				eliminated[index] = true;
				count = 0;
				remaining--;
			}
		}
		index = (index + 1) % n;
	}
	
	delete[] Jose;
	delete[] eliminated;
	return 0;
}


