#include <any>
#include <atcoder/dsu>
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

using namespace atcoder;

int main() {
    int N, M;
    cin >> N >> M;
    vector<long long> X(N);
    for (int i = 0; i < N; ++i) {
        cin >> X[i];
    }
    sort(X.begin(), X.end());

    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;
    dsu uf(N);
    int kichikyoku = N;
    for (int i = 0; i < N - 1; ++i) {
        pq.push({X[i + 1] - X[i], i});
    }
    while (kichikyoku > M) {
        auto [d, i] = pq.top();
        pq.pop();
        // if (uf.same(i, i + 1)) continue;
        uf.merge(i, i + 1);
        kichikyoku--;
    }

    vector<long long> left(N, 1LL << 60), right(N, -1);
    set<int> leaders;
    for (int i = 0; i < N; ++i) {
        left[uf.leader(i)] = min(left[uf.leader(i)], X[i]);
        right[uf.leader(i)] = max(right[uf.leader(i)], X[i]);
        leaders.insert(uf.leader(i));
    }

    long long ans = 0;
    for (int leader : leaders) {
        ans += right[leader] - left[leader];
    }

    cout << ans << endl;

    return 0;
}
