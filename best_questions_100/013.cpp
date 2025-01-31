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
    int R, C;
    cin >> R >> C;
    vector<vector<int>> A(R, vector<int>(C));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> A[i][j];
        }
    }

    int ans = 0;
    // ビットが立っている行を反転させる
    for (int bits=0; bits < (1<<R); bits++) {
        int sum = 0;
        for (int i = 0; i < C; i++) {
            // 裏側が焼けている枚数をカウント
            int cnt = 0;
            for (int j = 0; j < R; j++) {
                if (bits & (1<<j) and A[j][i] == 1) {
                    cnt++;
                } else if ((bits & (1<<j)) == 0 and A[j][i] == 0) {
                    cnt++;
                }
            }
            sum += max(cnt, R-cnt);
        }
        ans = max(ans, sum);
    }
    cout << ans << endl;

    return 0;
}
