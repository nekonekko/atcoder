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
    int D, N;
    cin >> D >> N;
    vector<int> T(D);
    for (int i = 0; i < D; i++) {
        cin >> T[i];
    }
    vector<int> A(N), B(N), C(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }

    // dp[i][j]: i日目にj番目の服を着たときの最大値
    vector<vector<int>> dp(D, vector<int>(N, 0));
    for (int i = 1; i < D; i++) {
        // j: i-1日目の服
        for (int j = 0; j < N; j++) {
            if (T[i - 1] < A[j] or T[i - 1] > B[j]) {
                continue;
            }
            // k: i日目の服
            for (int k = 0; k < N; k++) {
                if (T[i] < A[k] or T[i] > B[k]) {
                    continue;
                }
                dp[i][k] = max(dp[i][k], dp[i - 1][j] + abs(C[j] - C[k]));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, dp[D - 1][i]);
    }
    cout << ans << endl;
    return 0;
}
