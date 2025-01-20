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

bool check(long long mid, int N, long long M, vector<long long> &P) {
    if (mid > M) {
        return false;
    }

    long long cost = 0;
    for (int i = 0; i < N; i++) {
        long long k = (mid + P[i]) / (2 * P[i]);
        if ((2 * k - 1) * P[i] == mid) {
            k--;
        }
        if (k <= 0) {
            continue;
        }
        if (k * P[i] > (M - cost) / k) {
            return false;
        }
        cost += k * k * P[i];
        if (cost > M) {
            return false;
        }
    }
    return true;
}

int main() {
    // std::ifstream in("input_e.txt");
    // std::cin.rdbuf(in.rdbuf());

    int N;
    long long M;
    cin >> N >> M;
    vector<long long> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }

    long long left, right;
    left = 0; 
    right = M;
    while (right - left > 1) {
        long long mid = (left + right) / 2;
        if (check(mid, N, M, P)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    long long ans = 0;
    long long just_count = 0;
    long long cost = 0;
    for (int i = 0; i < N; i++) {
        long long k = floor((static_cast<long double>(left) / static_cast<long double>(P[i]) + 1) / 2);
        if ((2 * k - 1) * P[i] == left) {
            just_count++;
            k--;
        }
        ans += k;
        cost += k * k * P[i];
    }
    while (just_count > 0 && cost + left <= M) {
        cost += left;
        just_count--;
        ans++;
    }

    cout << ans << endl;

    return 0;
}
