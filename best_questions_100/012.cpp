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
    vector<vector<bool>> connected(N, vector<bool>(N, false));
    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        connected[x - 1][y - 1] = true;
        connected[y - 1][x - 1] = true;
    }

    int ans = 0;
    for (int bit = 0; bit < (1 << N); ++bit) {
        bool ok = true;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (bit & (1 << i) && bit & (1 << j)) {
                    if (!connected[i][j]) {
                        ok = false;
                        break;
                    }
                }
                if (!ok) {
                    break;
                }
            }
            if (!ok) {
                break;
            }
        }
        if (ok) {
            ans = max(ans, __builtin_popcount(bit));
        }
    }

    cout << ans << endl;
    
    return 0;
}
