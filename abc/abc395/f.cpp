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

bool ok(long long h, const vector<long long>& U, const vector<long long>& D,
        long long X) {
    int N = U.size();
    long long reduce = (U[0] + D[0]) - h;
    if (reduce < 0) {
        return false;
    }
    long long min_u = max(U[0] - reduce, 0LL);
    long long max_u = min(U[0], h);

    for (int i = 1; i < N; i++) {
        reduce = (U[i] + D[i]) - h;
        if (reduce < 0) {
            return false;
        }
        long long next_min_u = max(U[i] - reduce, 0LL);
        long long next_max_u = min(U[i], h);

        // cout << "min_u: " << min_u << ", max_u: " << max_u
        //      << ", next_min_u: " << next_min_u << ", next_max_u: " <<
        //      next_max_u
        //      << endl;

        if (max_u + X < next_min_u || next_max_u + X < min_u) {
            return false;
        }
        max_u = min(max_u + X, next_max_u);
        min_u = max(min_u - X, next_min_u);
    }

    return true;
}

int main() {
    int N;
    long long X;
    cin >> N >> X;
    vector<long long> U(N), D(N);
    long long min_h = 1LL << 60;
    for (int i = 0; i < N; i++) {
        cin >> U[i] >> D[i];
        min_h = min(min_h, U[i] + D[i]);
    }

    long long left = 0;
    long long right = 1LL << 60;
    while (right - left > 1) {
        long long mid = (left + right) / 2;
        if (ok(mid, U, D, X)) {
            // cout << mid << " is ok" << endl;
            left = mid;
        } else {
            // cout << mid << " is not ok" << endl;
            right = mid;
        }
    }

    // cout << left << endl;

    long long ans = 0;
    for (int i = 0; i < N; i++) {
        ans += (U[i] + D[i] - left);
    }
    cout << ans << endl;

    return 0;
}
