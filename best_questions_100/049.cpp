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

const int INF = 1e9;

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<pair<int, int>>> G(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        G[s].push_back({t, d});
    }
    // dp[i][j][S]: i を始点とし、今 j の頂点を訪れていて、訪れた頂点の集合が S
    // であるときの最小コスト
    vector<vector<vector<int>>> dp(
        V, vector<vector<int>>(V, vector<int>(1 << V, INF)));
    for (int i = 0; i < V; i++) {
        dp[i][i][1 << i] = 0;
    }

    // i: 始点
    for (int i = 0; i < V; i++) {
        // S: 訪れた頂点の集合
        for (int S = 0; S < (1 << V); S++) {
            // 始点が未訪問の場合
            if (!(S & (1 << i))) {
                continue;
            }
            // j: 現在の頂点
            for (int j = 0; j < V; j++) {
                // j を訪れていない場合
                if (!(S & (1 << j))) {
                    continue;
                }
                // このような経路が存在しない場合
                if (dp[i][j][S] == INF) {
                    continue;
                }
                // t: 次の頂点, d: j から t へのコスト
                for (auto [t, d] : G[j]) {
                    // t が訪問済みの場合
                    if (S & (1 << t)) {
                        continue;
                    }
                    // i から t へのコストを更新
                    dp[i][t][S | (1 << t)] =
                        min(dp[i][t][S | (1 << t)], dp[i][j][S] + d);
                }
            }
        }
    }

    // 戻るコスト込みで計算
    int ans = INF;
    // i: 始点
    for (int i = 0; i < V; i++) {
        // j: 始点に戻る直前に通った頂点
        for (int j = 0; j < V; j++) {
            for (auto [t, d] : G[j]) {
                // t が始点でない場合
                if (t != i) {
                    continue;
                }
                // t が始点の場合
                ans = min(ans, dp[i][j][(1 << V) - 1] + d);
            }
        }
    }
    cout << (ans == INF ? -1 : ans) << endl;

    return 0;
}
