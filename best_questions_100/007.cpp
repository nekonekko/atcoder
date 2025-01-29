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

bool isin(int x, int y) {
    return 0 <= x && x <= 5000 && 0 <= y && y <= 5000;
}

int main() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    vector<vector<bool>> exist(5001, vector<bool>(5001, false));
    for (int i = 0; i < n; ++i) {
        exist[x[i]][y[i]] = true;
    }

    int ans = 0;
    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            int dx = x[second] - x[first];
            int dy = y[second] - y[first];
            int third_x, third_y, fourth_x, fourth_y;
            // 候補1つ目
            third_x = x[second] - dy;
            third_y = y[second] + dx;
            fourth_x = x[first] - dy;
            fourth_y = y[first] + dx;
            if (isin(third_x, third_y) && isin(fourth_x, fourth_y) && exist[third_x][third_y] && exist[fourth_x][fourth_y]) {
                ans = max(ans, dx*dx + dy*dy);
                continue;
            }
            // 候補2つ目
            third_x = x[first] + dy;
            third_y = y[first] - dx;
            fourth_x = x[second] + dy;
            fourth_y = y[second] - dx;
            if (isin(third_x, third_y) && isin(fourth_x, fourth_y) && exist[third_x][third_y] && exist[fourth_x][fourth_y]) {
                ans = max(ans, dx*dx + dy*dy);
            }
        }
    }
    cout << ans << endl;

    return 0;
}
