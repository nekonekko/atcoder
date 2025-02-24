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
    int N, M, K, S;
    cin >> N >> M >> K >> S;
    int P, Q;
    cin >> P >> Q;
    vector<int> C(K);
    for (int i = 0; i < K; i++) {
        cin >> C[i];
        C[i]--;
    }
    vector<vector<int>> G_without_weight(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G_without_weight[a].push_back(b);
        G_without_weight[b].push_back(a);
    }
    // 0: 安全, 1: 危険, 2: ゾンビ
    vector<int> city_type(N, 0);
    queue<pair<int, int>> danger;
    vector<bool> visited(N, false);
    for (int i = 0; i < K; i++) {
        city_type[C[i]] = 2;
        danger.push(make_pair(C[i], 0));
    }
    while (!danger.empty()) {
        auto [u, d] = danger.front();
        danger.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (int v : G_without_weight[u]) {
            if (visited[v] || city_type[v] == 2) {
                continue;
            }
            city_type[v] = 1;
            if (d + 1 < S) {
                danger.push(make_pair(v, d + 1));
            }
        }
    }

    vector<vector<pair<int, int>>> G_with_weight(N);
    for (int i = 0; i < N; i++) {
        if (city_type[i] == 2) {
            continue;
        }
        for (int j : G_without_weight[i]) {
            if (j == N - 1) {
                G_with_weight[i].push_back(make_pair(j, 0));
                continue;
            }
            if (city_type[j] == 2) {
                continue;
            }
            G_with_weight[i].push_back(make_pair(j, city_type[j] == 0 ? P : Q));
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
        for (auto [v, w] : G_with_weight[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    cout << dist[N - 1] << endl;

    return 0;
}
