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
    vector<string> S(5);
    for (int i = 0; i < 5; i++) {
        cin >> S[i];
    }

    // 0: red, 1: blud, 2: white, 3: black
    vector<vector<int>> color(N, vector<int>(4));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < N; j++) {
            if (S[i][j] == 'R') {
                color[j][0]++;
            } else if (S[i][j] == 'B') {
                color[j][1]++;
            } else if (S[i][j] == 'W') {
                color[j][2]++;
            } else if (S[i][j] == '#') {
                color[j][3]++;
            }
        }
    }

    // dp[i][j]: i列目の色をjにするときの、i列め以前の塗り替え回数の最小値
    vector<vector<int>> dp(N, vector<int>(3, 1e9));
    for (int i = 0; i < 3; i++) {
        dp[0][i] = 5 - color[0][i];
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            // j: i列目の色
            // l: i-1列目の色
            for (int k = 0; k < 3; k++) {
                if (j == k) {
                    // 同じ色の列が隣り合ってはいけない
                    continue;
                }
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + (5 - color[i][j]));
            }
        }
    }
    int ans = 1e9;
    for (int i = 0; i < 3; i++) {
        ans = min(ans, dp[N - 1][i]);
    }
    cout << ans << endl;

    return 0;
}
