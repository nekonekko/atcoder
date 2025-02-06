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
    int N, W;
    cin >> N >> W;
    vector<int> v(N), w(N);
    map<int, int> mp;
    for (int i = 0; i < N; i++) {
        cin >> v[i] >> w[i];
    }

    vector<int> dp(W + 1, -1);
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= W; j++) {
            if (j - w[i] >= 0 && dp[j - w[i]] != -1) {
                dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= W; j++) {
        ans = max(ans, dp[j]);
    }
    cout << ans << endl;
    return 0;
}
