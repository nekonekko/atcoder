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

#define INF 1e9

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> C(N);
    vector<bool> bean_exist(N, false);
    for (int i = 1; i < N; i++) {
        cin >> C[i];
    }
    for (int i = 1; i < N; i++) {
        int a;
        cin >> a;
        if (a == 1) {
            bean_exist[i] = true;
        }
    }

    vector<int> before_been_idx(N, -1);
    int before_been = -1;
    for (int i = 1; i < N; i++) {
        if (!bean_exist[i]) {
            continue;
        }
        if (C[i] == i) {
            // cout << "C[i] = " << C[i] << endl;
            before_been_idx[i] = 0;
            before_been = i;
            continue;
        }
        before_been_idx[i] = before_been;
        before_been = i;
    }
    // for (int i = 0; i < N; i++) {
    //     cout << "before_been_idx[" << i << "] = " << before_been_idx[i] <<
    //     endl;
    // }

    // 1つ前の bean までの最短路を求める
    int ans = 0;
    for (int i = N - 1; i > 0; i--) {
        if (!bean_exist[i]) {
            continue;
        }
        if (before_been_idx[i] == 0) {
            ans += 1;
            continue;
        }
        if (before_been_idx[i] == -1) {
            before_been_idx[i] = 0;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            que;
        vector<int> dist(N, INF);
        dist[i] = 0;
        que.push({0, i});
        while (!que.empty()) {
            auto [d, v] = que.top();
            que.pop();
            if (dist[v] < d || v == before_been_idx[i]) {
                continue;
            }
            for (int j = 1; j <= C[v]; j++) {
                int u = v - j;
                if (u < 0 || u < before_been_idx[i]) {
                    break;
                }
                if (dist[u] > dist[v] + 1) {
                    dist[u] = dist[v] + 1;
                    que.push({dist[u], u});
                }
            }
        }
        // cout << "dist[" << i << "] = " << dist[before_been_idx[i]] << endl;
        ans += dist[before_been_idx[i]];
    }
    cout << ans << endl;

    return 0;
}
