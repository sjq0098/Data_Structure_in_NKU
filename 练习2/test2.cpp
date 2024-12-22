#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int n;
bool x[26];
void find(int k, int n) {
	if (k > n - 1) {
		for (int i = 0; i < n; i++) {
			if (x[i]) {
				cout << char('a' + i) << " ";
			}
		}
		cout << endl;
	}
	else
		for (int i = 0; i <= 1; i++) {
			x[k] = i;
			find(k + 1, n);
		}
}
int main() {
	for (int i = 0; i < n; i++) {
		x[i] = 0;
	}
	int k;
	ifstream in("input.txt");
	in>>k;
	if (k > 26 || k < 0) {
		cout << "WRONG" << endl;
		return 0;
	}
	find(0, k);
	return 0;
}
