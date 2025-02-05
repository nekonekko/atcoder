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

    vector<int> dist(N, -1);
    queue<int> que;
    que.push(0);
    dist[0] = 0;
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int u : G[v]) {
            if (dist[u] != -1) {
                continue;
            }
            dist[u] = dist[v] + 1;
            que.push(u);
        }
    }

    for (int i = 0; i < N; i++) {
        cout << i + 1 << " " << dist[i] << endl;
    }
    return 0;
}
