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

void no_and_exit() {
    cout << "No" << endl;
    exit(0);
}

int dfs(int v, vector<vector<int>>& G, int N, int K, vector<bool>& visited) {
    int s_v = 1;
    visited[v] = true;
    int n_children = 0;
    for (auto u : G[v]) {
        if (visited[u]) continue;
        int s_u = dfs(u, G, N, K, visited);
        if (s_u > 0) {
            n_children++;
            s_v += s_u;
        }
    }
    visited[v] = false;
    // cout << "v: " << v << " s_v: " << s_v << " n_children: " << n_children
    //      << endl;
    if (s_v < K) {
        if (n_children >= 2) {
            no_and_exit();
        }
    } else if (s_v == K) {
        if (n_children >= 3) {
            no_and_exit();
        }
        s_v = 0;
    } else {
        no_and_exit();
    }
    return s_v;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<vector<int>> G(N * K);
    for (int i = 0; i < N * K - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vector<bool> visited(N * K, false);
    dfs(0, G, N, K, visited);

    cout << "Yes" << endl;

    return 0;
}
