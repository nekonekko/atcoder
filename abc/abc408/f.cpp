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

int op(int a, int b) { return max(a, b); }

int e() { return -1; }

int main() {
    int N, D, R;
    cin >> N >> D >> R;

    vector<int> H(N);
    map<int, int> h_to_idx;
    for (int i = 0; i < N; ++i) {
        cin >> H[i];
        h_to_idx[H[i]] = i;
    }

    segtree<int, op, e> seg(N);
    vector<int> memo(N, -1);
    for (auto [h, i] : h_to_idx) {
        if (h <= D) {
            continue;
        }
        seg.set(h_to_idx[h - D], max(0, memo[h_to_idx[h - D]]));
        int max_jump = seg.prod(max(0, i - R), min(N, i + R + 1));
        memo[h_to_idx[h]] = max_jump + 1;
        // debug
        // for (int j = 0; j < N; ++j) {
        //     cout << H[j] << ":" << memo[j] << " ";
        // }
        // cout << endl;
    }
    int ans = *max_element(memo.begin(), memo.end());
    cout << (ans == -1 ? 0 : ans) << endl;

    return 0;
}
