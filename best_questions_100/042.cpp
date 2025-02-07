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
    int N, M;
    cin >> N >> M;
    vector<int> D(N), C(M);
    for (int i = 0; i < N; i++) {
        cin >> D[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> C[i];
    }

    // dp[i][j]: i日目に都市jにいるときの最小合計疲労度
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, 1e9));
    dp[0][0] = 0;
    for (int i = 1; i <= M; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= N; j++) {
            dp[i][j] =
                min(dp[i - 1][j - 1] + D[j - 1] * C[i - 1], dp[i - 1][j]);
        }
    }

    cout << dp[M][N] << endl;
    return 0;
}
