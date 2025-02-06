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

vector<pair<int, int>> get_around_pos(int x, int y) {
    if (y % 2 == 0) {
        return {
            {x - 1, y - 1}, {x, y - 1},     {x - 1, y},
            {x + 1, y},     {x - 1, y + 1}, {x, y + 1},
        };
    }
    return {
        {x, y - 1}, {x + 1, y - 1}, {x - 1, y},
        {x + 1, y}, {x, y + 1},     {x + 1, y + 1},
    };
}

int bfs(int i, int j, int W, int H, vector<vector<int>> &mat,
        vector<vector<bool>> &visited) {
    int res = 0;
    queue<pair<int, int>> que;
    que.push({j, i});
    visited[i][j] = true;
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (auto [nx, ny] : get_around_pos(x, y)) {
            if (nx < 0 || nx >= W || ny < 0 || ny >= H) {
                continue;
            }
            if (visited[ny][nx]) {
                continue;
            }
            if (mat[ny][nx] == 1) {
                res++;
                continue;
            }
            que.push({nx, ny});
            visited[ny][nx] = true;
        }
    }
    return res;
}

int main() {
    int W, H;
    cin >> W >> H;
    vector<vector<int>> mat(H + 2, vector<int>(W + 2, 0));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> mat[i + 1][j + 1];
        }
    }

    int ans = 0;
    vector<vector<bool>> visited(H + 2, vector<bool>(W + 2, false));
    ans += bfs(0, 0, W + 2, H + 2, mat, visited);

    cout << ans << endl;

    return 0;
}
