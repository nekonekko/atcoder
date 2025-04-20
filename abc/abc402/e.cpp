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
    int N, X;
    cin >> N >> X;
    vector<int> S(N), C(N);
    vector<long double> P(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i] >> C[i] >> P[i];
        P[i] /= 100;
    }
    vector<vector<long double>> dp(1 << N, vector<long double>(X + 1, 0));
    for (int x = 0; x <= X; ++x) {
        for (int s = 0; s < (1 << N); ++s) {
            for (int i = 0; i < N; ++i) {
                int ss = s | (1 << i);
                int xx = x - C[i];
                if (ss == s || xx < 0) continue;
                dp[s][x] = max(dp[s][x], P[i] * (dp[ss][xx] + S[i]) +
                                             (1 - P[i]) * dp[s][xx]);
            }
        }
    }

    // debug
    // for (int s = 0; s < (1 << N); ++s) {
    //     for (int x = 0; x <= X; ++x) {
    //         cout << dp[s][x] << " ";
    //     }
    //     cout << endl;
    // }

    cout << fixed << setprecision(15) << dp[0][X] << endl;
    return 0;
}
