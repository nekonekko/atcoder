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

long long INF = 1LL << 60;

int main() {
    int N, M;
    long long X;
    cin >> N >> M >> X;
    vector<vector<int>> G(N);
    vector<vector<int>> rG(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        rG[b].push_back(a);
    }
    vector<long long> dist(N, INF);
    vector<long long> rdist(N, INF);
    dist[0] = 0;
    rdist[0] = X;
    // {dist, node, is_reverse}
    priority_queue<tuple<long long, int, bool>,
                   vector<tuple<long long, int, bool>>,
                   greater<tuple<long long, int, bool>>>
        pq;
    pq.push({0, 0, false});
    pq.push({X, 0, true});
    while (!pq.empty()) {
        auto [d, node, is_reverse] = pq.top();
        pq.pop();
        if (is_reverse) {
            if (rdist[node] < d) {
                continue;
            }
            // reverseのまま進む
            for (auto to : rG[node]) {
                if (rdist[to] > d + 1) {
                    rdist[to] = d + 1;
                    pq.push({rdist[to], to, true});
                }
            }
            // 正しい向きで進む
            for (auto to : G[node]) {
                if (dist[to] > d + X + 1) {
                    dist[to] = d + X + 1;
                    pq.push({dist[to], to, false});
                }
            }
        } else {
            if (dist[node] < d) {
                continue;
            }
            // 正しい向きのまま進む
            for (auto to : G[node]) {
                if (dist[to] > d + 1) {
                    dist[to] = d + 1;
                    pq.push({dist[to], to, false});
                }
            }
            // reverseで進む
            for (auto to : rG[node]) {
                if (rdist[to] > d + X + 1) {
                    rdist[to] = d + X + 1;
                    pq.push({rdist[to], to, true});
                }
            }
        }
    }
    cout << min(dist[N - 1], rdist[N - 1]) << endl;

    return 0;
}
