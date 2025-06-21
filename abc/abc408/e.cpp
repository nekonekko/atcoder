#include <any>
#include <atcoder/all>
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

struct Edge {
    int from, to, label;
};

int main() {
    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        int u, v, label;
        cin >> u >> v >> label;
        edges[i] = {u - 1, v - 1, label};
    }

    int x = (1 << 30) - 1;
    for (int k = 29; k >= 0; --k) {
        int mask = (1 << k);
        int next_x = x & ~mask;
        dsu uf(N);
        for (const Edge& edge : edges) {
            if ((edge.label | next_x) == next_x) {
                uf.merge(edge.from, edge.to);
            }
        }
        if (uf.same(0, N - 1)) {
            x = next_x;
        }
    }

    cout << x << endl;

    return 0;
}
