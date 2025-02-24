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
    int N, M;
    cin >> N >> M;
    vector<vector<long long>> G(N, vector<long long>(N, 1e18));
    for (int i = 0; i < N; i++) {
        G[i][i] = 0;
    }
    for (int i = 0; i < M; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--;
        b--;
        G[a][b] = t;
        G[b][a] = t;
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (G[i][k] == 1e18 || G[k][j] == 1e18) {
                    continue;
                }
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
    long long min_max_time = 1e18;
    for (int i = 0; i < N; i++) {
        long long max_time = 0;
        for (int j = 0; j < N; j++) {
            max_time = max(max_time, G[i][j]);
        }
        if (max_time < min_max_time) {
            min_max_time = max_time;
        }
    }
    cout << min_max_time << endl;
    return 0;
}
