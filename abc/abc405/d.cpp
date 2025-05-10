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
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    for (int i = 0; i < H; i++) {
        cin >> S[i];
    }
    vector<vector<char>> ans(H, vector<char>(W, ' '));
    queue<tuple<int, int>> que;  // (x, y)
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (S[i][j] == 'E') {
                que.push({i, j});
                ans[i][j] = 'E';
            } else if (S[i][j] == '#') {
                ans[i][j] = '#';
            }
        }
    }
    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};
    vector<char> direction = {'<', '^', '>', 'v'};
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (ans[nx][ny] != ' ') {
                // 訪問済み、E, # の場合は無視
                continue;
            }
            ans[nx][ny] = direction[i];
            que.push({nx, ny});
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << ans[i][j];
        }
        cout << endl;
    }
    return 0;
}
