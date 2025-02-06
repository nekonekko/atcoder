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
        mp[w[i]] = max(mp[w[i]], v[i]);
    }

    vector<int> v2, w2;
    for (auto [weight, value] : mp) {
        v2.push_back(value);
        w2.push_back(weight);
    }

    vector<vector<int>> dp(v2.size() + 1, vector<int>(W + 1, -1));
    dp[0][0] = 0;
    for (int i = 0; i < v2.size(); i++) {
        for (int j = 0; j <= W; j++) {
            if (dp[i][j] == -1) {
                continue;
            }
            for (int k = 0; j + k * w2[i] <= W; k++) {
                dp[i + 1][j + k * w2[i]] =
                    max(dp[i + 1][j + k * w2[i]], dp[i][j] + k * v2[i]);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= W; j++) {
        ans = max(ans, dp[v2.size()][j]);
    }
    cout << ans << endl;
    return 0;
}
