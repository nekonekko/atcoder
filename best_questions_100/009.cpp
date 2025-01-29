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
    int M, N;
    cin >> M;
    vector<pair<int, int>> constellation(M);
    for (int i = 0; i < M; ++i) {
        cin >> constellation[i].first >> constellation[i].second;
    }
    cin >> N;
    vector<pair<int, int>> stars(N);
    for (int i = 0; i < N; ++i) {
        cin >> stars[i].first >> stars[i].second;
    }

    // 星iが星座の星1番目である場合を探索
    int ans_x = 1e8;
    int ans_y = 1e8;
    for (int i = 0; i < N; ++i) {
        int dx = stars[i].first - constellation[0].first;
        int dy = stars[i].second - constellation[0].second;
        bool ok = true;
        for (int j = 1; j < M; ++j) {
            int x = constellation[j].first + dx;
            int y = constellation[j].second + dy;
            bool exist = false;
            for (int k = 0; k < N; ++k) {
                if (i == k) continue;
                if (stars[k].first == x && stars[k].second == y) {
                    exist = true;
                    break;
                }
            }
            if (!exist) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans_x = dx;
            ans_y = dy;
            break;
        }
    }
    cout << ans_x << " " << ans_y << endl;

    return 0;
}
