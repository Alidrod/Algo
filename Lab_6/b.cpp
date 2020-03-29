// Copyright 2020 Edgar Zhivaev

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <functional>

using namespace std;

class HashMap {
 private:
    struct Entry {
        string key;
        string value;

        Entry(string key, string value) : key(std::move(key)),
                                                        value(std::move(value)) {}
    };
    hash<string> str_hash;
    const uint32_t HASH_SIZE = 50000;
    vector<vector<Entry> > array;
    uint32_t getHash(const string &value) {
        return str_hash(value) % HASH_SIZE;
    }

 public:
    HashMap() {
        array.resize(HASH_SIZE);
    }

    void put(const string &key, const string &value) {
        uint32_t index = getHash(key);
        for (auto &it : array[index]) {
            if (it.key == key) {
                it.value = value;
                return;
            }
        }
        array[index].emplace_back(key, value);
    }
    void remove(const string &key) {
        uint32_t index = getHash(key);
        for (auto &it : array[index]) {
            if (it.key == key) {
                it.value = "none";
                return;
            }
        }
    }
    string get(const string &key) {
        uint32_t index = getHash(key);
        for (auto &it : array[index]) {
            if (it.key == key) {
                return it.value;
            }
        }
        return "none";
    }
};

int main() {
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    HashMap hashMap;
    string type;
    string key;
    string value;
    while (cin >> type >> key) {
        if (type == "put") {
            cin >> value;
            hashMap.put(key, value);
        }
        if (type == "get") {
            cout << hashMap.get(key) << "\n";
        }
        if (type == "delete") {
            hashMap.remove(key);
        }
    }
    return 0;
}
