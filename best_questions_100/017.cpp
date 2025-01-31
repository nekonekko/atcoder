#include <any>
#include <cassert>
#include <cfenv>
#include <cfloat>
#include <charconv>
#include <cinttypes>
#include <ciso646>
#include <clocale>
#include <codecvt>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <ctgmath>
#include <forward_list>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <regex>
#include <scoped_allocator>
#include <set>
#include <shared_mutex>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <variant>

using namespace std;

void dfs(int K, vector<bool> &tate, vector<bool> &yoko, vector<bool> &naname1,
         vector<bool> &naname2, vector<pair<int, int>> &pos) {
    // cout << "K: " << K << endl;
    // for (int i = 0; i < 8; i++) {
    //     cout << "(" << pos[i].first << ", " << pos[i].second << ") ";
    // }
    // cout << endl;
    if (K == 8) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                auto exist = find(pos.begin(), pos.end(), make_pair(i, j));
                if (exist != pos.end()) {
                    cout << "Q";
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }
        exit(0);
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tate[i] || yoko[j] || naname1[i + j] || naname2[i - j + 7]) {
                continue;
            }
            tate[i] = true;
            yoko[j] = true;
            naname1[i + j] = true;
            naname2[i - j + 7] = true;
            pos[K] = make_pair(i, j);
            dfs(K + 1, tate, yoko, naname1, naname2, pos);
            tate[i] = false;
            yoko[j] = false;
            naname1[i + j] = false;
            naname2[i - j + 7] = false;
            pos[K] = make_pair(-1, -1);
        }
    }
}

int main() {
    int K;
    cin >> K;
    // naname1: 右上から左下, naname2: 左上から右下
    vector<bool> tate(8), yoko(8), naname1(15), naname2(15);
    vector<pair<int, int>> pos(8);
    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;
        tate[x] = true;
        yoko[y] = true;
        naname1[x + y] = true;
        naname2[x - y + 7] = true;
        pos[i] = make_pair(x, y);
    }
    dfs(K, tate, yoko, naname1, naname2, pos);

    return 0;
}
