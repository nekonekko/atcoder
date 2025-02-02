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
    vector<int> A(pow(3, N));
    string A_str;
    cin >> A_str;
    for (int i = 0; i < pow(3, N); i++) {
        A[i] = A_str[i] - '0';
    }

    vector<vector<int>> a_log(N, vector<int>(pow(3, N), 9));
    for (int i = 0; i < pow(3, N); i++) {
        a_log[0][i] = A[i];
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < pow(3, (N - i)); j++) {
            vector<int> tmp = {a_log[i - 1][3 * j], a_log[i - 1][3 * j + 1],
                               a_log[i - 1][3 * j + 2]};
            sort(tmp.begin(), tmp.end());
            // 000->0
            // 001->0
            // 011->1
            // 111->1
            a_log[i][j] = tmp[1];
        }
    }

    vector<vector<int>> dp(N + 1, vector<int>(pow(3, N), 1e9));
    for (int i = 0; i < pow(3, N); i++) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < N + 1; i++) {
        for (int j = 0; j < pow(3, (N - i)); j++) {
            // cout << "i: " << i << " j: " << j << endl;
            // 前の数字が全て同じ値の場合
            if (a_log[i - 1][3 * j] == a_log[i - 1][3 * j + 1] and
                a_log[i - 1][3 * j + 1] == a_log[i - 1][3 * j + 2]) {
                // cout << "all same" << endl;
                // 2こ変える必要がある
                // 全部足して、一番多いのを引けばいい
                dp[i][j] = dp[i - 1][3 * j] + dp[i - 1][3 * j + 1] +
                           dp[i - 1][3 * j + 2] -
                           max({dp[i - 1][3 * j], dp[i - 1][3 * j + 1],
                                dp[i - 1][3 * j + 2]});
                continue;
            }
            // 1つ目と2つ目が同じ場合
            if (a_log[i - 1][3 * j] == a_log[i - 1][3 * j + 1]) {
                // cout << "1st and 2nd same" << endl;
                dp[i][j] = min(dp[i - 1][3 * j], dp[i - 1][3 * j + 1]);
                continue;
            }
            // 2つ目と3つ目が同じ場合
            if (a_log[i - 1][3 * j + 1] == a_log[i - 1][3 * j + 2]) {
                // cout << "2nd and 3rd same" << endl;
                dp[i][j] = min(dp[i - 1][3 * j + 1], dp[i - 1][3 * j + 2]);
                continue;
            }
            // 1つ目と3つ目が同じ場合
            if (a_log[i - 1][3 * j] == a_log[i - 1][3 * j + 2]) {
                // cout << "1st and 3rd same" << endl;
                dp[i][j] = min(dp[i - 1][3 * j], dp[i - 1][3 * j + 2]);
                continue;
            }
        }
    }

    // for (int i = 0; i < N + 1; i++) {
    //     for (int j = 0; j < pow(3, N); j++) {
    //         cout << dp[i][j];
    //     }
    //     cout << endl;
    // }

    cout << dp[N][0] << endl;

    return 0;
}
