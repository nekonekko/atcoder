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
    int V, E, r;
    cin >> V >> E >> r;
    vector<vector<pair<int, long long>>> G(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        long long d;
        cin >> s >> t >> d;
        G[s].push_back({t, d});
    }
    vector<long long> dist(V, 1e18);
    dist[r] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;
    pq.push({0, r});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] < d) {
            continue;
        }
        for (auto [nv, nd] : G[v]) {
            if (dist[nv] > dist[v] + nd) {
                dist[nv] = dist[v] + nd;
                pq.push({dist[nv], nv});
            }
        }
    }
    for (int i = 0; i < V; i++) {
        if (dist[i] == 1e18) {
            cout << "INF" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
    return 0;
}
