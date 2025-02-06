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

const int MOD = 10000;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> schedule(N, -1);
    for (int i = 0; i < K; i++) {
        int A, B;
        cin >> A >> B;
        schedule[A - 1] = B - 1;
    }

    // dp[i][j][k]:
    // i日目に(0-indexed)
    // パスタjを食べる(0-indexed)
    // パスタjはk日連続で食べている(0-indexed)
    vector<vector<vector<int>>> dp(N,
                                   vector<vector<int>>(3, vector<int>(2, 0)));

    // 0日目の値を入れて初期化
    if (schedule[0] == -1) {
        for (int j = 0; j < 3; j++) {
            dp[0][j][0] = 1;
        }
    } else {
        dp[0][schedule[0]][0] = 1;
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            // j: 前の日に食べたパスタ
            for (int k = 0; k < 2; k++) {
                // k: jを連続で食べている日数(iを除く)
                for (int jj = 0; jj < 3; jj++) {
                    // jj: 今日食べるパスタ
                    if (schedule[i] != -1 and jj != schedule[i]) {
                        // 予定が決まっているが、今日のパスタが違う
                        continue;
                    }
                    if (j == jj) {
                        if (k == 1) {
                            continue;
                        }
                        dp[i][jj][k + 1] += dp[i - 1][j][k];
                        dp[i][jj][k + 1] %= MOD;
                    } else {
                        dp[i][jj][0] += dp[i - 1][j][k];
                        dp[i][jj][0] %= MOD;
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 2; k++) {
            ans += dp[N - 1][j][k];
            ans %= MOD;
        }
    }
    cout << ans << endl;

    return 0;
}
