// Copyright 2020 Edgar Zhivaev

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <functional>

using namespace std;

class LinkedMap {
 private:
    struct Node {
        string key;
        string value;
        Node *prev;
        Node *next;

        Node(string key, string value) : key(std::move(key)),
                                         value(std::move(value)) {
            prev = next = nullptr;
        }

        static void pair(Node *a, Node *b) {
            if (a != nullptr) {
                a->next = b;
            }
            if (b != nullptr) {
                b->prev = a;
            }
        }

        static void erase(Node *a) {
            a->value.clear();
            a->prev = a->next = nullptr;
        }
    };

    Node *tail;
    vector<vector<Node *> > array;
    hash<string> str_hash;
    const uint32_t HASH_SIZE = 50000;

    uint32_t getHash(const string &value) {
        return str_hash(value) % HASH_SIZE;
    }

 public:
    LinkedMap() {
        tail = nullptr;
        array.resize(HASH_SIZE);
    }

    Node *find(const string &key) {
        uint32_t index = getHash(key);
        for (auto &it : array[index]) {
            if (it->key == key) {
                return it;
            }
        }
        return nullptr;
    }

    void put(const string &key, const string &val) {
        Node *it = find(key);
        if (it && !it->value.empty()) {
            it->value = val;
            return;
        }
        Node *newNode;
        if (it == nullptr) {
            newNode = new Node(key, val);
            array[getHash(key)].push_back(newNode);
        } else {
            newNode = it;
            newNode->value = val;
        }
        Node::pair(tail, newNode);
        tail = newNode;
    }

    string get(const string &key) {
        Node *it = find(key);
        if (it && !it->value.empty()) {
            return it->value;
        }
        return "none";
    }

    void remove(const string &key) {
        Node *it = find(key);
        if (it == nullptr || it->value.empty()) {
            return;
        }
        if (it == tail) {
            tail = tail->prev;
        }
        Node::pair(it->prev, it->next);
        Node::erase(it);
    }

    string next(const string &key) {
        Node *it = find(key);
        if (it == nullptr || it->next == nullptr) {
            return "none";
        }
        return it->next->value;
    }

    string prev(const string &key) {
        Node *it = find(key);
        if (it == nullptr || it->prev == nullptr) {
            return "none";
        }
        return it->prev->value;
    }
};

int main() {
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    LinkedMap linkedMap;
    string type;
    string key;
    string value;
    while (cin >> type >> key) {
        if (type == "put") {
            cin >> value;
            linkedMap.put(key, value);
        }
        if (type == "delete") {
            linkedMap.remove(key);
        }
        if (type == "get") {
            cout << linkedMap.get(key) << "\n";
        }
        if (type == "next") {
            cout << linkedMap.next(key) << "\n";
        }
        if (type == "prev") {
            cout << linkedMap.prev(key) << "\n";
        }
    }
    return 0;
}
