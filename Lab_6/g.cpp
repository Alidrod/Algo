// Copyright 2020 Edgar Zhivaev

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const uint64_t p = 1000000007;

uint64_t binpow(uint64_t a, uint64_t n) {
    uint64_t res = 1;
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

vector<vector<uint32_t > > a;
vector<uint32_t> par;
vector<uint64_t> hashVec;
uint32_t dmax;
uint32_t mirr;

void findMirr(uint32_t v, uint32_t pre, uint32_t depth) {
    par[v] = pre;
    if (a[v].size() == 1 && a[v][0] == pre) {
        if (depth > dmax) {
            dmax = depth;
            mirr = v;
        }
        return;
    }
    for (uint32_t u : a[v]) {
        if (u != pre) {
            findMirr(u, v, depth + 1);
        }
    }
}

void calcHash(uint32_t v, uint32_t pre) {
    if (a[v].size() == 1) {
        hashVec[v] = 1;
        return;
    }
    if (hashVec[v] != 0) {
        return;
    }
    for (auto &u : a[v]) {
        if (u != pre) {
            calcHash(u, v);
            hashVec[v] += binpow(p, hashVec[u]);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    uint32_t n;
    cin >> n;
    if (n == 1) {
        cout << "NO";
        return 0;
    }
    a.resize(n);
    par.resize(n);
    hashVec.resize(n, 0);
    for (uint32_t i = 0; i < n - 1; ++i) {
        uint32_t v, u;
        cin >> v >> u;
        v--;
        u--;
        a[v].push_back(u);
        a[u].push_back(v);
    }

    uint32_t l, r, distant;
    findMirr(1, UINT32_MAX, 0);
    l = mirr;
    dmax = 0;

    findMirr(l, UINT32_MAX, 0);
    r = mirr;
    distant = dmax;
    if (distant % 2 == 1) {
        cout << "NO";
        return 0;
    }
    uint32_t mid = r;
    for (uint32_t i = 0; i < distant / 2; ++i) {
        mid = par[mid];
    }
    if (a[mid].size() != 2) {
        cout << "NO";
        return 0;
    }
    calcHash(a[mid][0], mid);
    calcHash(a[mid][1], mid);
    if (hashVec[a[mid][0]] == hashVec[a[mid][1]]) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
