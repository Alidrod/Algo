// Copyright 2020 Edgar Zhivaev

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <functional>

using namespace std;

hash<string> str_hash;


struct Node {
    string value;
    Node *prev;
    Node *next;

    explicit Node(string value) : value(std::move(value)) {
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

class NamedLinkedHashSet {
 private:
    string key;
    Node *tail;
    uint32_t count;
    vector<vector<Node *> > array;
    uint32_t HASH_TABLE_SIZE = 2;
    uint32_t getHash(const string &value) {
        return str_hash(value) % HASH_TABLE_SIZE;
    }

    Node *find(const string &val);
    void increase() {
        HASH_TABLE_SIZE = HASH_TABLE_SIZE * 2;
        vector<vector<Node *> > newArray(HASH_TABLE_SIZE);
        for (auto &it : array) {
            for (auto &jt : it) {
                newArray[getHash(jt->value)].push_back(jt);
            }
        }
        array = newArray;
    }

 public:
    explicit NamedLinkedHashSet(string key) {
        this->key = move(key);
        count = 0;
        tail = nullptr;
        array.resize(HASH_TABLE_SIZE);
    }

    [[nodiscard]] const string &getKey() const;

    void put(const string &val);

    void remove(const string &val);

    void getAll(vector<string> *out);
};

Node *NamedLinkedHashSet::find(const string &val) {
    uint32_t index = getHash(val);
    for (auto &it : array[index]) {
        if (it->value == val) {
            return it;
        }
    }
    return nullptr;
}

void NamedLinkedHashSet::put(const string &val) {
    Node *it = find(val);
    if (it) {
        return;
    }
    Node *newNode;
    newNode = new Node(val);
    array[getHash(val)].push_back(newNode);
    Node::pair(tail, newNode);
    tail = newNode;
    count++;
    if (count > HASH_TABLE_SIZE / 2) {
        increase();
    }
}

void NamedLinkedHashSet::remove(const string &val) {
    Node *it = find(val);
    if (it == nullptr) {
        return;
    }
    if (it == tail) {
        tail = tail->prev;
    }
    Node::pair(it->prev, it->next);
    Node::erase(it);
}

void NamedLinkedHashSet::getAll(vector<string> *out) {
    Node *curr = tail;
    while (curr) {
        out->push_back(curr->value);
        curr = curr->prev;
    }
}

const string &NamedLinkedHashSet::getKey() const {
    return key;
}

class MultiHashMap {
 private:
    vector<vector<NamedLinkedHashSet *> > array;
    NamedLinkedHashSet ** find(const string &key);
    const uint32_t HASH_TABLE_SIZE = 50000;
    uint32_t getHash(const string &value) {
        return str_hash(value) % HASH_TABLE_SIZE;
    }

 public:
    MultiHashMap() {
        array.resize(HASH_TABLE_SIZE);
    }

    void put(const string &key, const string &val);

    void remove(const string &key, const string &val);

    void get(const string &key, vector<string> *out);

    void removeAll(const string &key);
};

NamedLinkedHashSet ** MultiHashMap::find(const string &key) {
    for (auto &it : array[getHash(key)]) {
        if (it->getKey() == key) {
            return &it;
        }
    }
    return nullptr;
}

void MultiHashMap::put(const string &key, const string &val) {
    auto it = find(key);
    if (it == nullptr) {
        array[getHash(key)].push_back(nullptr);
        it = &array[getHash(key)].back();
        (*it) = new NamedLinkedHashSet(key);
    }
    (*it)->put(val);
}

void MultiHashMap::remove(const string &key, const string &val) {
    auto it = find(key);
    if (it == nullptr) {
        return;
    }
    (*it)->remove(val);
}

void MultiHashMap::get(const string &key, vector<string> *out) {
    auto it = find(key);
    out->clear();
    if (it == nullptr) {
        return;
    }
    (*it)->getAll(out);
}

void MultiHashMap::removeAll(const string &key) {
    auto it = find(key);
    if (it == nullptr) {
        return;
    }
    (*it) = new NamedLinkedHashSet(key);
}

int main() {
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    MultiHashMap map;
    auto *out = new vector<string>;
    string type;
    string key;
    string value;
    while (cin >> type >> key) {
        if (type == "put") {
            cin >> value;
            map.put(key, value);
        }
        if (type == "delete") {
            cin >> value;
            map.remove(key, value);
        }
        if (type == "get") {
            map.get(key, out);
            cout << out->size() << " ";
            for (auto &it : *out) {
                cout << it << " ";
            }
            cout << "\n";
        }
        if (type == "deleteall") {
            map.removeAll(key);
        }
    }
    return 0;
}
