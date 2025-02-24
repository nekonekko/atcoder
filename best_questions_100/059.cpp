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
    int N, K;
    cin >> N >> K;
    vector<int> C(N), R(N);
    for (int i = 0; i < N; i++) {
        cin >> C[i] >> R[i];
    }
    vector<vector<int>> edges(N);
    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    vector<vector<pair<int, int>>> G(N);
    for (int i = 0; i < N; i++) {
        queue<pair<int, int>> q;
        q.push(make_pair(i, 0));
        vector<bool> visited(N, false);
        while (!q.empty()) {
            auto [u, d] = q.front();
            q.pop();
            if (visited[u]) {
                continue;
            }
            visited[u] = true;
            if (d == R[i]) {
                continue;
            }
            for (int v : edges[u]) {
                if (visited[v]) {
                    continue;
                }
                G[i].push_back(make_pair(v, C[i]));
                q.push(make_pair(v, d + 1));
            }
        }
    }

    vector<long long> dist(N, 1e18);
    dist[0] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;
    pq.push(make_pair(0, 0));
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) {
            continue;
        }
        for (auto [v, w] : G[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    cout << dist[N - 1] << endl;
    return 0;
}
