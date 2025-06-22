#include <any>
#include <atcoder/modint>
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
using mint = modint998244353;
#define MOD 998244353

int main() {
    int N;
    cin >> N;
    vector<pair<long long, int>> testcases(N);
    for (int i = 0; i < N; i++) {
        cin >> testcases[i].first >> testcases[i].second;
    }

    // dp[i][j] := sum of positive integers that satisfies
    // x < 2^i and
    // popcount(x) = j
    vector<vector<mint>> dp(65, vector<mint>(65, 0));
    vector<vector<mint>> dp_count(65, vector<mint>(65, 0));
    for (int i = 0; i <= 61; i++) {
        dp[i][0] = 0;
        dp_count[i][0] =
            1;  // There's one way to have popcount 0 (the number 0)
        dp[i][i] = ((1LL << i) - 1);  // All numbers with popcount i
        dp_count[i][i] =
            1;  // There's one way to have popcount i (the number itself)
    }
    for (int i = 1; i <= 61; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i - 1][j];
            dp[i][j] += dp[i - 1][j - 1];
            dp[i][j] += ((1LL << (i - 1)) * dp_count[i - 1][j - 1]);
            dp_count[i][j] = dp_count[i - 1][j] + dp_count[i - 1][j - 1];
        }
    }

    for (int i = 0; i < N; i++) {
        long long x = testcases[i].first;
        int popcount = testcases[i].second;

        if (x == 0) {
            cout << 0 << endl;
            continue;
        }

        vector<int> bits(62, 0);
        for (int j = 0; j < 62; j++) {
            if (x & (1LL << j)) {
                bits[j] = 1;
            } else {
                bits[j] = 0;
            }
        }
        // cout << "bits: " << bits << ", idx: " << idx << endl;

        mint ans = 0;
        mint prod = 0;
        int count = 0;
        for (int j = 61; j >= 0; j--) {
            if (bits[j] == 0) {
                continue;
            }
            if (count <= popcount) {
                ans += dp[j][popcount - count];
                ans += (prod * dp_count[j][popcount - count]);
            }
            count++;
            prod += (1LL << j);
        }
        if (count == popcount) {
            ans += prod;
        }
        cout << ans.val() << endl;
    }

    // debug
    // for (int i = 0; i < 5; i++) {
    //     for (int j = 1; j <= i + 1; j++) {
    //         cout << "dp[" << i << "][" << j << "] = " << dp[i][j]
    //              << ", count = " << dp_count[i][j] << endl;
    //     }
    // }

    return 0;
}
