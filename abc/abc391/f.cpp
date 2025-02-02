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

long long calc(long long a, long long b, long long c) {
    return a * b + b * c + c * a;
}

int main() {
    int N, K;
    cin >> N >> K;
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
    sort(A.begin(), A.end(), greater<long long>());
    sort(B.begin(), B.end(), greater<long long>());
    sort(C.begin(), C.end(), greater<long long>());
    priority_queue<tuple<long long, int, int, int>> pq;
    pq.push(make_tuple(calc(A[0], B[0], C[0]), 0, 0, 0));
    set<tuple<int, int, int>> s;
    s.insert(make_tuple(0, 0, 0));
    while (K > 0) {
        auto q = pq.top();
        long long sum = get<0>(q);
        int a = get<1>(q);
        int b = get<2>(q);
        int c = get<3>(q);
        pq.pop();
        // cout << K << " " << sum << " " << a << " " << b << " " << c << endl;
        K--;
        if (K == 0) {
            cout << sum << endl;
            return 0;
        }
        if (a + 1 < N) {
            if (s.find(make_tuple(a + 1, b, c)) == s.end()) {
                s.insert(make_tuple(a + 1, b, c));
                pq.push(make_tuple(calc(A[a + 1], B[b], C[c]), a + 1, b, c));
            }
        }
        if (b + 1 < N) {
            if (s.find(make_tuple(a, b + 1, c)) == s.end()) {
                s.insert(make_tuple(a, b + 1, c));
                pq.push(make_tuple(calc(A[a], B[b + 1], C[c]), a, b + 1, c));
            }
        }
        if (c + 1 < N) {
            if (s.find(make_tuple(a, b, c + 1)) == s.end()) {
                s.insert(make_tuple(a, b, c + 1));
                pq.push(make_tuple(calc(A[a], B[b], C[c + 1]), a, b, c + 1));
            }
        }
    }

    return 0;
}
