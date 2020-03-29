// Copyright 2020 Edgar Zhivaev

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class HashSet {
 private:
    const uint32_t HASH_LENGTH = 50000;
    vector<vector<int64_t> > array;

    uint32_t getHash(int64_t val) {
        if (val < 0) {
            val = -val;
        }
        return static_cast<uint32_t>(val) % HASH_LENGTH;
    }

 public:
    HashSet() {
        array.resize(HASH_LENGTH);
    }

    bool exists(int64_t val) {
        uint32_t index = getHash(val);
        for (auto it : array[index]) {
            if (it == val) {
                return true;
            }
        }
        return false;
    }

    void insert(int64_t val) {
        if (exists(val)) {
            return;
        }
        uint32_t index = getHash(val);
        array[index].push_back(val);
        }

    void remove(int64_t val) {
        uint32_t index = getHash(val);
        for (auto &it : array[index]) {
            if (it == val) {
                it = INT64_MAX;
            }
        }
    }
};


int main() {
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    HashSet hashSet;
    string inp;
    int64_t val;
    while (cin >> inp >> val) {
        if (inp == "insert") {
            hashSet.insert(val);
        }
        if (inp == "delete") {
            hashSet.remove(val);
        }
        if (inp == "exists") {
            if (hashSet.exists(val)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
        if (inp.empty()) {
            break;
        }
    }
    return 0;
}
