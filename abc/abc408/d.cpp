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
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        string S;
        cin >> S;
        vector<vector<int>> dp(N + 1, vector<int>(3, INT_MAX));
        dp[0][0] = 0;
        dp[0][1] = 0;
        dp[0][2] = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '0') {
                dp[i + 1][0] = dp[i][0];
                dp[i + 1][1] = min(dp[i][0] + 1, dp[i][1] + 1);
                dp[i + 1][2] = min(dp[i][1], dp[i][2]);
            } else {
                dp[i + 1][0] = dp[i][0] + 1;
                dp[i + 1][1] = min(dp[i][0], dp[i][1]);
                dp[i + 1][2] = min(dp[i][1] + 1, dp[i][2] + 1);
            }
        }
        int ans = min({dp[N][0], dp[N][1], dp[N][2]});
        cout << ans << endl;
    }
    return 0;
}
