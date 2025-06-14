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
    int N, H, M;
    cin >> N >> H >> M;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
    }

    vector<vector<int>> dp(N + 1, vector<int>(M + 1, -1));
    dp[0][M] = H;
    for (int i = 0; i < N; i++) {
        for (int m = 0; m <= M; m++) {
            if (m + B[i] <= M && dp[i][m + B[i]] != -1) {
                dp[i + 1][m] = max(dp[i + 1][m], dp[i][m + B[i]]);
            }
            if (dp[i][m] >= A[i]) {
                dp[i + 1][m] = max(dp[i + 1][m], dp[i][m] - A[i]);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int m = 0; m <= M; m++) {
            if (dp[i][m] != -1) {
                ans = i;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
