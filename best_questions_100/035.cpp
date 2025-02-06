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
    int N, W;
    cin >> N >> W;
    vector<int> v(N), w(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i] >> w[i];
    }
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, -1));
    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= W; j++) {
            if (dp[i][j] != -1) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                if (j + w[i] <= W) {
                    dp[i + 1][j + w[i]] =
                        max(dp[i + 1][j + w[i]], dp[i][j] + v[i]);
                }
            }
        }
    }
    int ans = 0;
    for (int j = 0; j <= W; j++) {
        ans = max(ans, dp[N][j]);
    }
    cout << ans << endl;
    return 0;
}
