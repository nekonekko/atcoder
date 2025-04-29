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
    int N, K;
    cin >> N >> K;
    int M = 0;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        M = max(M, A[i]);
    }
    vector<int> cnt(M + 1);
    vector<int> baisu_cnt(M + 1);
    for (int i = 0; i < N; i++) {
        cnt[A[i]]++;
    }
    for (int i = 1; i <= M; i++) {
        for (int j = i; j <= M; j += i) {
            baisu_cnt[i] += cnt[j];
        }
    }
    vector<int> ans(M + 1, 0);
    // debug
    // for (int i = 1; i <= M; i++) {
    //     cout << "baisu_cnt[" << i << "] = " << baisu_cnt[i] << endl;
    // }
    for (int i = 1; i <= M; i++) {
        if (baisu_cnt[i] < K) {
            continue;
        }
        for (int j = i; j <= M; j += i) {
            ans[j] = max(ans[j], i);
        }
    }

    for (int i = 0; i < N; i++) {
        cout << ans[A[i]] << endl;
    }

    return 0;
}
