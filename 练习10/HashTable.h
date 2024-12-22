#pragma once
using namespace std;
template<class E, class K>
class HashTable {
    int hSearch(const K& k) const;
    int div;
    E* htcontent;
    bool* neverUsed; // judge if htc[i] is non-empty;
    int non_count();
    int realnon_count();
public:

    HashTable(int divisor) {
        div = divisor;
        htcontent = new E[div];
        neverUsed = new bool[div];

        for (int i = 0; i < div; i++) {
            htcontent[i] = 0;
            neverUsed[i] = true;
        }
    }

    ~HashTable() { delete[] htcontent;  delete[] neverUsed; }
    bool Search(const K& k, E& e) const;
    HashTable<E, K>& Insert(const E& e);
    HashTable<E, K>& Remove(const E& e);
    HashTable<E, K>& Reset();
    void Output();
};

template<class E, class K>
int HashTable<E, K>::hSearch(const K& k) const
{
    int i = k % div;
    int j = i;
    do {
        if (neverUsed[j] || htcontent[j] == k) return j;
        j = (j + 1) % div;
    } while (j != i);

    return j;
}

template<class E, class K>
int HashTable<E, K>::non_count()
{
    int nc = 0;
    for (int i = 0; i < div; i++) {
        if (!htcontent[i]) {
            nc++;
        }
    }
    return nc;
}

template<class E, class K>
int HashTable<E, K>::realnon_count()
{
    int rnc = 0;
    for (int i = 0; i < div; i++) {
        if (neverUsed[i] && !htcontent[i]) {
            rnc++;
        }
    }
    return rnc;
}

template<class E, class K>
bool HashTable<E, K>::Search(const K& k, E& e) const
{
    int b = hSearch(k); //find the index;
    if (neverUsed[b] || htcontent[b] != k) return false;
    e = htcontent[b];
    return true;
}

template<class E, class K>
HashTable<E, K>& HashTable<E, K>::Insert(const E& e)
{
    K k = e; // extract key
    int b = hSearch(k);

    if (neverUsed[b]) {
        neverUsed[b] = false;
        htcontent[b] = e;
        return *this;
    }

    if (htcontent[b] == k) {
        std::cout << "Has been duplicated!" << std::endl;
    }
    else {
        std::cout << "Full!" << std::endl;
    }
    return *this;
}

template<class E, class K>
HashTable<E, K>& HashTable<E, K>::Remove(const E& e)
{
    K k = e; // extract key
    int b = hSearch(k);
    E tmp{};
    if (!Search(e, tmp)) {
        return *this;
    }
    if (htcontent[b]) {
        htcontent[b] = 0;
        int index = b;
        do {
            if (neverUsed[index]) return *this;
            if (htcontent[index] == e) {
                swap(htcontent[index], htcontent[b]);
                return *this;
            }
            index = (index + 1) % div;
        } while (index != b);
    }
    return *this;
}

template<class E, class K>
HashTable<E, K>& HashTable<E, K>::Reset()
{
    float rate = float(realnon_count()) / float(non_count());
    if (rate < 0.4000)
        for (int i = 0; i < div; i++) {
            if (!neverUsed[i] && htcontent[i] == 0) {
                neverUsed[i] = true;
            }
        }
    return *this;
}

template<class E, class K>
void HashTable<E, K>::Output()
{
    for (int i = 0; i < div; i++) {
        if (neverUsed[i]) {
            std::cout << "NULL";
        }
        else {
            std::cout << htcontent[i];
        }
        if (i != div) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}