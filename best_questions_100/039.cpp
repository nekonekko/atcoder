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
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    vector<vector<long long>> dp(N, vector<long long>(21, 0));
    dp[0][A[0]] = 1;
    for (int i = 1; i < N - 1; i++) {
        for (int j = 0; j <= 20; j++) {
            if (j + A[i] <= 20) {
                dp[i][j + A[i]] += dp[i - 1][j];
            }
            if (j - A[i] >= 0) {
                dp[i][j - A[i]] += dp[i - 1][j];
            }
        }
    }

    cout << dp[N - 2][A[N - 1]] << endl;
    return 0;
}
