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

void solve(const vector<int> &W, int N, vector<vector<int>> &can_slide) {
    for (int width = 2; width <= N; width += 2) {
        for (int i = 0; i < N; i++) {
            int j = (i + width - 1);
            if (j >= N) {
                break;
            }
            if (width == 2) {
                if (abs(W[i] - W[j]) <= 1) {
                    can_slide[i][j] = 1;
                } else {
                    can_slide[i][j] = 0;
                }
            } else {
                if (abs(W[i] - W[j]) <= 1 && can_slide[i + 1][j - 1] == 1) {
                    can_slide[i][j] = 1;
                } else {
                    for (int k = i + 1; k < j; k += 2) {
                        if (can_slide[i][k] == 1 && can_slide[k + 1][j] == 1) {
                            can_slide[i][j] = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int count(const vector<vector<int>> &can_slide, int i, int N, vector<int> &dp) {
    if (i == N) {
        return 0;
    }
    if (dp[i] != -1) {
        return dp[i];
    }
    int res = 0;
    for (int j = i; j < N; j++) {
        if (can_slide[i][j] == 1) {
            res = max(res, count(can_slide, j + 1, N, dp) + (j - i + 1));
        }
    }
    res = max(res, count(can_slide, i + 1, N, dp));
    dp[i] = res;
    return res;
}

int main() {
    while (true) {
        int N;
        cin >> N;
        if (N == 0) {
            break;
        }
        vector<int> W(N);
        for (int i = 0; i < N; i++) {
            cin >> W[i];
        }
        vector<vector<int>> can_slide(N, vector<int>(N, -1));
        solve(W, N, can_slide);

        // dp[i]: i から N - 1 までの区間でスライドできる個数の最大値
        vector<int> dp(N, -1);
        int ans = count(can_slide, 0, N, dp);
        cout << ans << endl;
    }
    return 0;
}
