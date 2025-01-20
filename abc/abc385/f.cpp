#include <cassert>
#include <cfenv>
#include <cfloat>
#include <ciso646>
#include <clocale>
#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cinttypes>
#include <charconv>
#include <typeindex>
#include <any>
#include <scoped_allocator>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <valarray>
#include <variant>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <condition_variable>
#include <shared_mutex>
#include <codecvt>
#include <future>
#include <regex>
#include <iostream>
#include <random>
#include <ctgmath>
#include <fstream>
#include <iomanip>

using namespace std;

long double INF = 1e18;

int main() {
    int N;
    cin >> N;

    vector<long long> X(N+1), H(N+1);
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> H[i];
    }

    long double ans = -INF;
    for (int i = 1; i < N; i++) {
        long double vs_prev;
        vs_prev = static_cast<long double>(H[i - 1] * X[i] - H[i] * X[i - 1]) / static_cast<long double>(X[i] - X[i-1]);

        if (ans < vs_prev) {
            ans = vs_prev;
        }
    }

    if (ans < 0) {
        cout << -1 << endl;
    } else {
        cout << fixed << setprecision(20) << ans << endl;
    }

    return 0;
}
