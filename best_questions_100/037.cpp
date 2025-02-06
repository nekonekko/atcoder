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
    vector<int> C(M);
    for (int i = 0; i < M; i++) {
        cin >> C[i];
    }
    vector<int> dp(N + 1, 1e9);
    dp[0] = 0;
    for (int i = 0; i < M; i++) {
        for (int j = C[i]; j <= N; j++) {
            dp[j] = min(dp[j], dp[j - C[i]] + 1);
        }
    }
    cout << dp[N] << endl;
    return 0;
}
