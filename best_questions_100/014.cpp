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

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    long long ans = 1e18;
    // ビットが立っている建物が見えるとする
    for (int bits=0; bits < (1<<N); bits++) {
        if (__builtin_popcount(bits) != K) {
            continue;
        }
        long long sum = 0;
        long long max_h = 0;
        for (int i = 0; i < N; i++) {
            if (bits & (1<<i)) {
                if (A[i] <= max_h) {
                    sum += max_h - A[i] + 1;
                    max_h++;
                } else {
                    max_h = A[i];
                }
            } else {
                max_h = max(max_h, A[i]);
            }
        }
        ans = min(ans, sum);
    }
    cout << ans << endl;

    return 0;
}
