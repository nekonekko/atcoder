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
    while (true) {
        int N, M;
        cin >> N >> M;
        if (N == 0 && M == 0) {
            break;
        }
        vector<int> C(M), X(N);
        for (int i = 0; i < M; i++) {
            cin >> C[i];
        }
        for (int i = 0; i < N; i++) {
            cin >> X[i];
        }

        // dp[i][j]: y_iの値がjのときの最小二乗和
        vector<vector<long long>> dp(N + 1, vector<long long>(256, 1e18));
        dp[0][128] = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= 255; j++) {
                if (dp[i][j] == 1e18) {
                    continue;
                }
                for (int k = 0; k < M; k++) {
                    int next = min(max(j + C[k], 0), 255);
                    dp[i + 1][next] =
                        min(dp[i + 1][next],
                            dp[i][j] + (X[i] - next) * (X[i] - next));
                }
            }
        }
        long long ans = 1e18;
        for (int i = 0; i <= 255; i++) {
            ans = min(ans, dp[N][i]);
        }
        cout << ans << endl;
    }
    return 0;
}
