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
    // 二分探索で解き直し
    int N, Q;
    cin >> N;
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    cin >> Q;
    vector<int> T(Q);
    for (int i = 0; i < Q; i++) {
        cin >> T[i];
    }

    int ans = 0;
    for (int i = 0; i < Q; i++) {
        // 自分で実装
        // int left = 0;
        // int right = N;
        // while (right - left > 1) {
        //     int mid = (left + right) / 2;
        //     if (S[mid] <= T[i]) {
        //         left = mid;
        //     } else {
        //         right = mid;
        //     }
        // }
        // if (S[left] == T[i]) {
        //     ans++;
        // }
        // STL も使ってみる
        auto iter = lower_bound(S.begin(), S.end(), T[i]);
        if (iter != S.end() && *iter == T[i]) {
            ans++;
        }
    }
    cout << ans << endl;

    return 0;
}
