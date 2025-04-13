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
    long long N;
    cin >> N;

    for (long long d = 1; d * d * d <= N; d++) {
        if (N % d != 0) {
            continue;
        }
        long long p = N / d;
        long long left = 0;
        long long right = 1e9;
        while (right - left > 1) {
            long long mid = (left + right) / 2;
            long long q = 3 * mid * mid + 3 * mid * d + d * d;
            if (q == p) {
                cout << d + mid << " " << mid << endl;
                return 0;
            }
            if (q < p) {
                left = mid;
            } else {
                right = mid;
            }
        }
        // if (3 * left * left + 3 * d * left + d * d == p) {
        //     cout << d + left << " " << left << endl;
        //     return 0;
        // }
    }
    cout << -1 << endl;
    return 0;
}
