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

int ans = INT_MAX;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> G(N);
    for (int i = 0; i < M; ++i) {
        int A, B;
        int W;
        cin >> A >> B >> W;
        --A;
        --B;
        G[A].emplace_back(B, W);
    }

    vector<vector<int>> visited(N, vector<int>(1024, false));
    visited[0][0] = true;

    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        auto [u, x] = q.front();
        q.pop();

        for (const auto& [v, w] : G[u]) {
            int new_xor = x ^ w;
            if (!visited[v][new_xor]) {
                visited[v][new_xor] = true;
                q.push({v, new_xor});
            }
        }
    }

    for (int i = 0; i < 1024; ++i) {
        if (visited[N - 1][i]) {
            ans = min(ans, i);
        }
    }

    cout << (ans == INT_MAX ? -1 : ans) << endl;
    return 0;
}
