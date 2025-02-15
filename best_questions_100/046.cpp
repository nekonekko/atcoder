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
    int N;
    cin >> N;
    vector<pair<int, int>> M(N);
    for (int i = 0; i < N; i++) {
        cin >> M[i].first >> M[i].second;
    }

    // dp[i][j]: 積 M_i ... M_j の計算に必要なスカラー乗算の最小の回数
    vector<vector<long long>> dp(N, vector<long long>(N, 1e18));
    for (int i = 0; i < N; i++) {
        dp[i][i] = 0;
    }
    for (int width = 1; width < N; width++) {
        for (int i = 0; i + width < N; i++) {
            int j = i + width;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] +
                                             (long long)M[i].first *
                                                 M[k].second * M[j].second);
            }
        }
    }
    cout << dp[0][N - 1] << endl;

    return 0;
}
