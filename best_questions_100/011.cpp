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
    vector<vector<bool>> connected(N, vector<bool>(M, false));
    for (int i = 0; i < M; ++i) {
        int K;
        cin >> K;
        for (int j = 0; j < K; ++j) {
            int l;
            cin >> l;
            connected[l - 1][i] = true;
        }
    }
    vector<int> P(M);
    for (int i = 0; i < M; ++i) {
        cin >> P[i];
    }

    int ans = 0;
    // ビットが立っている箇所のスイッチがON
    for (int bit = 0; bit < (1 << N); ++bit) {
        vector<int> cnt(M, 0);
        for (int i = 0; i < N; ++i) {
            // i番めのスイッチがONのとき
            if (bit & (1 << i)) {
                for (int j = 0; j < M; ++j) {
                    if (connected[i][j]) {
                        cnt[j]++;
                    }
                }
            }
        }
        bool ok = true;
        for (int i = 0; i < M; ++i) {
            if (cnt[i] % 2 != P[i]) {
                ok = false;
            }
        }
        if (ok) {
            ans++;
        }
    }
    cout << ans << endl;

    return 0;
}
