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
    int N;
    cin >> N;
    vector<long long> A(N), B(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
    }

    long long entrance = -1;
    long long min_time = 1LL << 60;
    for (int i = 0; i < N; ++i) {
        // A[i]が入口のとき
        long long time = 0;
        for (int j = 0; j < N; ++j) {
            time += abs(A[i] - A[j]);
        }
        if (time < min_time) {
            min_time = time;
            entrance = A[i];
        }
    }
    long long exit = -1;
    min_time = 1LL << 60;
    for (int i = 0; i < N; ++i) {
        // B[i]が出口のとき
        long long time = 0;
        for (int j = 0; j < N; ++j) {
            time += abs(B[i] - B[j]);
        }
        if (time < min_time) {
            min_time = time;
            exit = B[i];
        }
    }

    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        ans += abs(entrance - A[i]) + abs(A[i] - B[i]) + abs(B[i] - exit);
    }
    cout << ans << endl;

    return 0;
}
