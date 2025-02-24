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
    vector<vector<pair<int, int>>> G(N);
    for (int q = 0; q < K; q++) {
        int q_type;
        cin >> q_type;
        if (q_type == 1) {
            int c, d, e;
            cin >> c >> d >> e;
            c--;
            d--;
            G[c].push_back({d, e});
            G[d].push_back({c, e});
            continue;
        }

        int a, b;
        cin >> a >> b;
        a--;
        b--;
        vector<int> dist(N, 1e9);
        dist[a] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            pq;
        pq.push({0, a});
        while (not pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) {
                continue;
            }
            for (auto [v, w] : G[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        if (dist[b] == 1e9) {
            cout << -1 << endl;
        } else {
            cout << dist[b] << endl;
        }
    }
    return 0;
}
