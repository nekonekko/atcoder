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
    int N, Q;
    cin >> N >> Q;

    vector<vector<int>> G(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    vector<int> counter(N, 0);
    for (int i = 0; i < Q; i++) {
        int p, x;
        cin >> p >> x;
        p--;
        counter[p] += x;
    }
    queue<int> que;
    que.push(0);
    vector<bool> visited(N, false);
    visited[0] = true;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int u : G[v]) {
            if (visited[u]) {
                continue;
            }
            counter[u] += counter[v];
            visited[u] = true;
            que.push(u);
        }
    }
    for (int i = 0; i < N; i++) {
        cout << counter[i] << " ";
    }
    cout << endl;
    return 0;
}
