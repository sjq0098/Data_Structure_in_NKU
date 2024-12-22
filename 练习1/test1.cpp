/*#include<iostream>
#include<fstream>
using namespace std;
int main() {
	long long fibo[91];
	int x;
	ifstream fin("input.txt");
	fin >> x;
	fin.close();
	if (x > 90 || x < 0) {
		cout << "WRONG" << endl;
		return 0;
	}
	for (int i = 0; i <= x; i++) {
		if (i == 0) {
			fibo[i] = 0;
		} else if (i == 1 || i == 2) {
			fibo[i] = 1;
		} else {
			fibo[i] = fibo[i - 1] + fibo[i - 2];
		}
	}
	cout << fibo[x] << endl;
	return 0;
}
*/
#include<iostream>
#include<fstream>
using namespace std;
long long Fibonacci(long long *F, int n) {
	F[0] = 0;
	if (F[n] != 0 || n == 0) {
		return F[n];
	} else {
		F[n] = Fibonacci(F, n - 1) + Fibonacci(F, n - 2);
	}
	return F[n];
}
int main() {
	long long fibo[91];
	for (int i = 3; i < 91; i++) {
		fibo[i] = 0;
	}
	fibo[1] = fibo[2] = 1;
	int x;
	ifstream fin("input.txt");
	fin >> x;
	fin.close();
	if (x > 90 || x < 0) {
		cout << "WRONG" << endl;
		return 0;
	}
	cout << Fibonacci(fibo, x) << endl;
	return 0;
}


