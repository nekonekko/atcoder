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

int main() {
    int N, M;
    cin >> N >> M;
    // tuple<int, long long, long long>: (to, dist,time)
    vector<vector<tuple<int, long long, long long>>> G(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        long long c, d;
        cin >> a >> b >> c >> d;
        a--, b--;
        G[a].push_back({b, c, d});
        G[b].push_back({a, c, d});
    }

    // dp[j][S]: j の頂点を訪れており、訪問済みの頂点の集合が S
    // であるときの最短経路
    vector<vector<long long>> dp(N, vector<long long>(1 << N, 1e18));
    // pattern[i][j][S]: j の頂点を訪れており、訪問済みの頂点の集合が S
    // であるときの最短経路のパターン数
    vector<vector<long long>> pattern(N, vector<long long>(1 << N, 0));

    // 初期化
    dp[0][1] = 0;
    pattern[0][1] = 1;

    // S: 訪れた頂点の集合
    for (int S = 1; S < (1 << N); S++) {
        // u: 訪れている頂点
        for (int u = 0; u < N; u++) {
            // u が未訪問の場合
            if (!(S & (1 << u))) {
                continue;
            }
            // そのような経路がない場合
            if (dp[u][S] == 1e18) {
                continue;
            }
            // v: 次の頂点
            for (auto [v, dist, time] : G[u]) {
                // v が訪問済みの場合
                if (S & (1 << v)) {
                    continue;
                }
                // 道路が閉鎖済みの場合
                if (time < dp[u][S] + dist) {
                    continue;
                }
                // 今回の道が最短経路でない場合
                if (dp[v][S | (1 << v)] < dp[u][S] + dist) {
                    continue;
                }
                // 最短経路を更新する場合
                if (dp[v][S | (1 << v)] > dp[u][S] + dist) {
                    dp[v][S | (1 << v)] = dp[u][S] + dist;
                    pattern[v][S | (1 << v)] = pattern[u][S];
                    continue;
                }
                // 最短経路が同じ場合
                pattern[v][S | (1 << v)] += pattern[u][S];
            }
        }
    }

    long long min_dist = 1e18;
    long long min_pattern = 0;
    // 最後に頂点 i を訪れた
    for (int i = 1; i < N; i++) {
        // そのような経路がない場合
        if (dp[i][(1 << N) - 1] == 1e18) {
            continue;
        }
        // i から 0 への道が存在して、かつ通過できるかどうか
        long long return_dist = 1e18;
        for (auto [v, dist, time] : G[i]) {
            if (v != 0) {
                continue;
            }
            if (time < dp[i][(1 << N) - 1] + dist) {
                break;
            }
            return_dist = dist;
        }
        // 0 に戻れない場合
        if (return_dist == 1e18) {
            continue;
        }
        // 最短経路を更新する場合
        if (min_dist > dp[i][(1 << N) - 1] + return_dist) {
            min_dist = dp[i][(1 << N) - 1] + return_dist;
            min_pattern = pattern[i][(1 << N) - 1];
            continue;
        }
        // 最短経路が同じ場合
        if (min_dist == dp[i][(1 << N) - 1] + return_dist) {
            min_pattern += pattern[i][(1 << N) - 1];
        }
    }
    cout << (min_dist == 1e18
                 ? "IMPOSSIBLE"
                 : to_string(min_dist) + " " + to_string(min_pattern))
         << endl;

    return 0;
}
