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

const int MOD = 10007;

bool attend_manager(int attendances, char manager) {
    if (manager == 'J') {
        return (attendances & 1) != 0;
    } else if (manager == 'O') {
        return (attendances & 2) != 0;
    } else {
        return (attendances & 4) != 0;
    }
}

bool exist_same_attendance(int current, int prev) {
    return (current & prev) != 0;
}

int main() {
    int N;
    cin >> N;
    string S;
    cin >> S;

    // dp[i][j]: i 日目の出席者が j である場合の数
    // 001: J, 010: O, 100: I
    vector<vector<int>> dp(N, vector<int>(1 << 3, 0));
    for (int j = 0; j < 1 << 3; j++) {
        if (attend_manager(j, S[0]) && attend_manager(j, 'J')) {
            dp[0][j] = 1;
        }
    }

    for (int i = 1; i < N; i++) {
        // j: i 日目の出席者
        for (int j = 0; j < 1 << 3; j++) {
            if (!attend_manager(j, S[i])) {
                continue;
            }
            // k: i - 1 日目の出席者
            for (int k = 0; k < 1 << 3; k++) {
                if (!exist_same_attendance(j, k)) {
                    continue;
                }
                dp[i][j] += dp[i - 1][k];
                dp[i][j] %= MOD;
            }
        }
    }

    int ans = 0;
    for (int j = 0; j < 1 << 3; j++) {
        ans += dp[N - 1][j];
        ans %= MOD;
    }
    cout << ans << endl;

    return 0;
}
