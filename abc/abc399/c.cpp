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

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    // 連結成分に同じ色を塗る
    vector<int> color(N, -1);
    int current_color = 0;
    for (int i = 0; i < N; ++i) {
        if (color[i] != -1) continue;
        queue<int> q;
        q.push(i);
        color[i] = current_color;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : G[v]) {
                if (color[u] == -1) {
                    color[u] = current_color;
                    q.push(u);
                }
            }
        }
        current_color++;
    }
    // debug
    // for (int i = 0; i < N; ++i) {
    //     cout << color[i] << " ";
    // }
    // cout << endl;

    // その連結成分の頂点数と辺数を数える
    vector<int> cnt(N, 0);
    vector<int> edge_cnt(N, 0);
    for (int i = 0; i < N; ++i) {
        cnt[color[i]]++;
        edge_cnt[color[i]] += G[i].size();
    }
    for (int i = 0; i < N; ++i) {
        edge_cnt[i] /= 2;
    }
    // debug
    // for (int i = 0; i < N; ++i) {
    //     cout << cnt[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < N; ++i) {
    //     cout << edge_cnt[i] << " ";
    // }
    // cout << endl;

    // 木にするために削除する辺の数
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (cnt[i] == 0) continue;
        if (edge_cnt[i] > cnt[i] - 1) {
            ans += edge_cnt[i] - (cnt[i] - 1);
        }
    }
    cout << ans << endl;
    return 0;
}
