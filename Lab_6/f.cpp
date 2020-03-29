// Copyright 2020 Edgar Zhivaev

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <functional>

using namespace std;

int main() {
//    freopen("multimap.in", "r", stdin);
//    freopen("multimap.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    uint32_t k;
    cin >> k;
    for (uint32_t i = 0; i < k; i++) {
        string str;
        for (uint32_t j = 0; j < 11; j++) {
            if ((i & (1 << j)) > 0) {
                str += "rgeg";
            } else {
                str += "sIGH";
            }
        }
        cout << str << "\n";
    }
    return 0;
}
