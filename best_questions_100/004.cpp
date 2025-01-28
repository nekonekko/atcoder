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
    int N, M;
    cin >> N >> M;

    vector<vector<long long>> A(N, vector<long long>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> A[i][j];
        }
    }

    long long ans = 0;
    for (int song1 = 0; song1 < M - 1; song1++) {
        for (int song2 = song1 + 1; song2 < M; song2++) {
            long long sum = 0;
            for (int i = 0; i < N; i++) {
                sum += max(A[i][song1], A[i][song2]);
            }
            ans = max(ans, sum);
        }
    }
    cout << ans << endl;
}
