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
    int N;
    cin >> N;
    vector<long long> A(N), B(N), C(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    sort(C.begin(), C.end());

    vector<long long> a_under_b(N);
    for (int i = 0; i < N; i++) {
        auto it = lower_bound(A.begin(), A.end(), B[i]);
        a_under_b[i] = it - A.begin();
    }
    long long ans = 0;
    for (int i = 0; i < N; i++) {
        auto it = upper_bound(C.begin(), C.end(), B[i]);
        long long c_over_b = C.end() - it;
        ans += a_under_b[i] * c_over_b;
    }
    cout << ans << endl;

    return 0;
}
