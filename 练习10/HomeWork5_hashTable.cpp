#include<iostream>
#include "HashTable.h"
using namespace std;



int main() {
    int n = 0;
    cin >> n;
    HashTable<int, int> m(n);
    int ran[20] = { 23, 34, 21, 67, 45, 32, 87, 98, 56, 54, 90, 57, 87, 65, 43, 22, 99, 66, 47, 78 };
    for (int i = 0; i < n; i++) {
        m.Insert(ran[i]);
    }
    m.Output();
    for (int j = 0; j < 3; j++) {
        int tmp = 0;
        cin >> tmp;
        m.Remove(tmp);
        m.Output();
    }
    m.Reset().Output();
    return 0;
}