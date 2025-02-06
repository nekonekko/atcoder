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
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++) {
        string X, Y;
        cin >> X >> Y;
        int N = X.size();
        int M = Y.size();
        vector<vector<int>> dp(N, vector<int>(M, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (X[i] == Y[j]) {
                    dp[i][j] = 1;
                    if (i > 0 && j > 0) {
                        dp[i][j] += dp[i - 1][j - 1];
                    }
                } else {
                    if (i > 0) {
                        dp[i][j] = dp[i - 1][j];
                    }
                    if (j > 0) {
                        dp[i][j] = max(dp[i][j], dp[i][j - 1]);
                    }
                }
            }
        }
        cout << dp[N - 1][M - 1] << endl;
    }
    return 0;
}
