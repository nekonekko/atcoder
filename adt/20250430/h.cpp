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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int x, k;
        cin >> x >> k;
        --x;

        vector<bool> visited(N, false);
        visited[x] = true;
        queue<pair<int, int>> que;
        que.push({x, 0});
        int ans = x + 1;
        while (!que.empty()) {
            auto [v, d] = que.front();
            que.pop();
            if (d == k) {
                continue;
            }
            for (int nv : G[v]) {
                if (visited[nv]) {
                    continue;
                }
                visited[nv] = true;
                que.push({nv, d + 1});
                ans += nv + 1;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
