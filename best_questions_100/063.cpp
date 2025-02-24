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
    vector<vector<long long>> A(N, vector<long long>(N));
    vector<vector<long long>> B(N, vector<long long>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> A[i][j];
            B[i][j] = A[i][j];
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                B[i][j] = min(B[i][j], B[i][k] + B[k][j]);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != B[i][j]) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    priority_queue<tuple<long long, int, int>,
                   vector<tuple<long long, int, int>>>
        pq;
    long long ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            ans += A[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            pq.push(make_tuple(A[i][j], i, j));
        }
    }
    while (!pq.empty()) {
        auto [w, u, v] = pq.top();
        pq.pop();
        // (u, v) がなくても良いか検証
        bool ok = false;
        for (int k = 0; k < N; k++) {
            if (k == u || k == v) {
                continue;
            }
            if (A[u][v] == A[u][k] + A[k][v]) {
                ok = true;
                break;
            }
        }
        if (ok) {
            ans -= w;
        }
    }
    cout << ans << endl;

    return 0;
}
