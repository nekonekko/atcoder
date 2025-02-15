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
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    // dp[i][j]: JOI->IOI が食べた後に、区間[i, j] が食べられているときの JOI
    // の得点の最大値
    vector<vector<long long>> dp(N, vector<long long>(N, -1));
    for (int i = 0; i < N; i++) {
        // 最初に JOI が A[i] を食べる
        if (A[(i - 1 + N) % N] > A[(i + 1) % N]) {
            // IOI が A[(i - 1 + N) % N] を食べる
            dp[(i - 1 + N) % N][i] = max(dp[(i - 1 + N) % N][i], A[i]);
        } else {
            // IOI が A[(i + 1) % N] を食べる
            dp[i][(i + 1) % N] = max(dp[i][(i + 1) % N], A[i]);
        }
    }
    for (int width = 2; width <= N - 2; width += 2) {
        for (int i = 0; i < N; i++) {
            int j = (i + width - 1) % N;
            if (dp[i][j] == -1) {
                continue;
            }
            // 配るDP
            // JOI が A[(i - 1 + N) % N] を食べる場合
            if (A[(i - 2 + N) % N] > A[(j + 1 + N) % N]) {
                // IOI が A[(i - 2 + N) % N] を食べる
                dp[(i - 2 + N) % N][j] =
                    max(dp[(i - 2 + N) % N][j], dp[i][j] + A[(i - 1 + N) % N]);
            } else {
                // IOI が A[(j + 1) % N] を食べる
                dp[(i - 1 + N) % N][(j + 1) % N] =
                    max(dp[(i - 1 + N) % N][(j + 1) % N],
                        dp[i][j] + A[(i - 1 + N) % N]);
            }
            // JOI が A[(j + 1) % N] を食べる場合
            if (A[(i - 1 + N) % N] > A[(j + 2) % N]) {
                // IOI が A[(i - 1 + N) % N] を食べる
                dp[(i - 1 + N) % N][(j + 1) % N] =
                    max(dp[(i - 1 + N) % N][(j + 1) % N],
                        dp[i][j] + A[(j + 1) % N]);
            } else {
                // IOI が A[(j + 2) % N] を食べる
                dp[i][(j + 2) % N] =
                    max(dp[i][(j + 2) % N], dp[i][j] + A[(j + 1) % N]);
            }
        }
    }

    if (N % 2 != 0) {
        for (int i = 0; i < N; i++) {
            // A[i] が残っているとき
            if (dp[(i + 1) % N][(i - 1 + N) % N] != -1) {
                dp[i][(i - 1 + N) % N] =
                    max(dp[i][(i - 1 + N) % N],
                        dp[(i + 1) % N][(i - 1 + N) % N] + A[i]);
                dp[(i + 1) % N][i] =
                    max(dp[(i + 1) % N][i],
                        dp[(i + 1) % N][(i - 1 + N) % N] + A[i]);
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, dp[i][(i - 1 + N) % N]);
    }
    cout << ans << endl;

    return 0;
}
