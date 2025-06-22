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
    int H, W, N;
    cin >> H >> W >> N;
    vector<pair<int, int>> xy(N), yx(N);
    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        xy[i] = {x, y};
        yx[i] = {y, x};
    }
    sort(xy.begin(), xy.end());
    sort(yx.begin(), yx.end());

    vector<bool> x_used(H, false), y_used(W, false);
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int t, k;
        cin >> t >> k;
        --k;
        if (t == 1) {
            if (x_used[k]) {
                cout << 0 << endl;
                continue;
            }
            x_used[k] = true;
            auto left = lower_bound(xy.begin(), xy.end(), make_pair(k, 0));
            auto right = upper_bound(xy.begin(), xy.end(), make_pair(k, W));
            int ans = 0;
            while (left != right) {
                if (!y_used[left->second]) {
                    ++ans;
                }
                ++left;
            }
            cout << ans << endl;
        } else {
            if (y_used[k]) {
                cout << 0 << endl;
                continue;
            }
            y_used[k] = true;
            auto left = lower_bound(yx.begin(), yx.end(), make_pair(k, 0));
            auto right = upper_bound(yx.begin(), yx.end(), make_pair(k, H));
            int ans = 0;
            while (left != right) {
                if (!x_used[left->second]) {
                    ++ans;
                }
                ++left;
            }
            cout << ans << endl;
        }
    }

    return 0;
}
