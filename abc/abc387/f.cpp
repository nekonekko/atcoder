#include <cassert>
#include <cfenv>
#include <cfloat>
#include <ciso646>
#include <clocale>
#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cinttypes>
#include <charconv>
#include <typeindex>
#include <any>
#include <scoped_allocator>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <valarray>
#include <variant>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <condition_variable>
#include <shared_mutex>
#include <codecvt>
#include <future>
#include <regex>
#include <iostream>
#include <random>
#include <ctgmath>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

const long MOD = 998244353;

// from: https://drken1215.hatenablog.com/entry/2023/05/06/133900
struct SCC {
    using Edge = int;
    using SGraph = vector<vector<Edge>>;

    // input
    SGraph G, rG;

    // result
    vector<vector<int>> scc;
    vector<int> cmp;
    SGraph dag;

    // constructor
    SCC(int N) : G(N), rG(N) {}

    // add edge
    void addedge(int u, int v) {
        G[u].push_back(v);
        rG[v].push_back(u);
    }

    // decomp
    vector<bool> seen;
    vector<int> vs, rvs;
    void dfs(int v) {
        seen[v] = true;
        for (auto e : G[v]) if (!seen[e]) dfs(e);
        vs.push_back(v);
    }
    void rdfs(int v, int k) {
        seen[v] = true;
        cmp[v] = k;
        for (auto e : rG[v]) if (!seen[e]) rdfs(e, k);
        rvs.push_back(v);
    }

    // reconstruct
    set<pair<int,int>> newEdges;
    void reconstruct() {
        int N = (int)G.size();
        int dV = (int)scc.size();
        dag.assign(dV, vector<Edge>());
        newEdges.clear();
        for (int i = 0; i < N; ++i) {
            int u = cmp[i];
            for (auto e : G[i]) {
                int v = cmp[e];
                if (u == v) continue;
                if (!newEdges.count({u, v})) {
                    dag[u].push_back(v);
                    newEdges.insert({u, v});
                }
            }
        }
    }

    // main
    void solve() {
        // first dfs
        int N = (int)G.size();
        seen.assign(N, false);
        vs.clear();
        for (int v = 0; v < N; ++v) if (!seen[v]) dfs(v);

        // back dfs
        int k = 0;
        scc.clear();
        cmp.assign(N, -1);
        seen.assign(N, false);
        for (int i = N - 1; i >= 0; --i) {
            if (!seen[vs[i]]) {
                rvs.clear();
                rdfs(vs[i], k++);
                scc.push_back(rvs);
            }
        }

        // reconstruct
        reconstruct();
    }
};

template <typename T> using Graph = vector<vector<T>>;

int main() {
    int N, M;
    cin >> N >> M;

    SCC scc(N);
    for (int i = 0; i < N; ++i) {
        int A_i;
        cin >> A_i;
        A_i--;
        scc.addedge(A_i, i);
    }
    scc.solve();

    // for (int i = 0; i < N; ++i) {
    //     cout << scc.cmp[i] << endl;
    // }

    Graph<int> new_graph(scc.scc.size());
    Graph<int> new_graph_reversed(scc.scc.size());

    int outdegree[scc.scc.size()];

    for (int i = 0; i < scc.scc.size(); ++i) {
        outdegree[i] = 0;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < scc.G[i].size(); ++j) {
            int u = scc.cmp[i];
            int v = scc.cmp[scc.G[i][j]];
            if (u == v) continue;
            new_graph[u].push_back(v);
            new_graph_reversed[v].push_back(u);
            outdegree[u]++;
        }
    }

    vector<int> roots, leafs;
    for (int i = 0; i < scc.scc.size(); ++i) {
        if (new_graph[i].size() == 0) {
            leafs.push_back(i);
        }
        if (new_graph_reversed[i].size() == 0) {
            roots.push_back(i);
        }
    }

    // dp[i][j]: 頂点iがj以下の値をとる場合の数
    long dp[scc.scc.size()][M];
    for (int i = 0; i < scc.scc.size(); ++i) {
        for (int j = 0; j < M; ++j) {
            dp[i][j] = 1;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < leafs.size(); ++i) {
        q.push(leafs[i]);
        for (int j = 0; j < M; ++j) {
            dp[leafs[i]][j] = j + 1;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < new_graph_reversed[u].size(); ++i) {
            int v = new_graph_reversed[u][i];
            outdegree[v]--;

            // 他に未走査の子がいる場合はスキップ
            if (outdegree[v] != 0) continue;

            // 全ての子を走査済みの場合
            for (int j = 0; j < new_graph[v].size(); ++j) {
                int w = new_graph[v][j];
                for (int k = 0; k < M; ++k) {
                    dp[v][k] *= dp[w][k];
                    dp[v][k] %= MOD;
                }
            }
            for (int j = 1; j < M; ++j) {
                dp[v][j] += dp[v][j - 1];
                dp[v][j] %= MOD;
            }
            q.push(v);
        }
    }

    long ans = 1;
    for (int i = 0; i < roots.size(); ++i) {
        ans *= dp[roots[i]][M - 1];
        ans %= MOD;
    }

    cout << ans << endl;

    // for (int i = 0; i < scc.scc.size(); ++i) {
    //     cout << i << ": ";
    //     for (int j = 0; j < new_graph[i].size(); ++j) {
    //         cout <<  new_graph[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // for (int i = 0; i < scc.scc.size(); ++i) {
    //     cout << i << ": ";
    //     for (int j = 0; j < M; ++j) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}
