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
    vector<int> max_c(61, 0);
    vector<int> min_c(61, 1e9);
    for (int i = 0; i < N; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        for (int j = A; j <= B; j++) {
            max_c[j] = max(max_c[j], C);
            min_c[j] = min(min_c[j], C);
        }
    }

    vector<int> max_c_each_day(D, 0);
    vector<int> min_c_each_day(D, 1e9);
    for (int i = 0; i < D; i++) {
        max_c_each_day[i] = max_c[T[i]];
        min_c_each_day[i] = min_c[T[i]];
    }

    vector<vector<int>> dp(D, vector<int>(2, 0));
    for (int i = 1; i < D; i++) {
        dp[i][0] =
            max(dp[i - 1][0] + abs(max_c_each_day[i] - max_c_each_day[i - 1]),
                dp[i - 1][1] + abs(max_c_each_day[i] - min_c_each_day[i - 1]));
        dp[i][1] =
            max(dp[i - 1][0] + abs(min_c_each_day[i] - max_c_each_day[i - 1]),
                dp[i - 1][1] + abs(min_c_each_day[i] - min_c_each_day[i - 1]));
    }
    cout << max(dp[D - 1][0], dp[D - 1][1]) << endl;

    return 0;
}
