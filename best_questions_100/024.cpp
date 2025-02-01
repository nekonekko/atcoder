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

int dfs(int u, int t, const vector<vector<int>> &G, vector<int> &d,
        vector<int> &f) {
    d[u] = t;
    for (int v : G[u]) {
        if (d[v] == -1) {
            t = dfs(v, ++t, G, d, f);
        }
    }
    f[u] = ++t;
    return t;
}

int main() {
    int N;
    cin >> N;
    vector<vector<int>> G(N);
    for (int i = 0; i < N; i++) {
        int u, k;
        cin >> u >> k;
        for (int j = 0; j < k; j++) {
            int v;
            cin >> v;
            G[u - 1].push_back(v - 1);
        }
    }

    vector<int> d(N, -1);
    vector<int> f(N, -1);
    int t = 1;
    for (int i = 0; i < N; i++) {
        if (d[i] == -1) {
            t = dfs(i, t, G, d, f);
            t++;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << i + 1 << " " << d[i] << " " << f[i] << endl;
    }

    return 0;
}
