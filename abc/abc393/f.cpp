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

#define INF 1e9 + 7

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    vector<vector<pair<int, int>>> mp(N);
    for (int i = 0; i < Q; i++) {
        int R, X;
        cin >> R >> X;
        R--;
        mp[R].emplace_back(X, i);
    }
    vector<int> dp(N + 1, INF);
    vector<int> ans(Q);
    for (int i = 0; i < N; i++) {
        // LIS の更新
        auto itr = lower_bound(dp.begin(), dp.end(), A[i]);
        *itr = A[i];
        // debug
        // for (int j = 0; j <= N; j++) {
        //     cout << dp[j] << " ";
        // }
        // cout << endl;
        // クエリを読む
        for (auto [X, idx] : mp[i]) {
            // dp の中で X より大きい最小の値を探す
            auto itr = upper_bound(dp.begin(), dp.end(), X);
            // その値のインデックスを求める
            ans[idx] = distance(dp.begin(), itr);
            // cout << *itr << endl;
        }
    }
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
