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
    vector<string> field(H);
    for (int i = 0; i < H; i++) {
        cin >> field[i];
    }

    vector<int> pos_x(N + 1), pos_y(N + 1);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (field[i][j] == 'S') {
                pos_x[0] = j;
                pos_y[0] = i;
                continue;
            }
            if ('1' <= field[i][j] && field[i][j] <= char('0' + N)) {
                int cheese_factory = field[i][j] - '0';
                pos_x[cheese_factory] = j;
                pos_y[cheese_factory] = i;
            }
        }
    }
    vector<int> dx = {1, 0, -1, 0};
    vector<int> dy = {0, 1, 0, -1};
    int ans = 0;
    for (int hp = 1; hp <= N; hp++) {
        int sx = pos_x[hp - 1];
        int sy = pos_y[hp - 1];
        int gx = pos_x[hp];
        int gy = pos_y[hp];
        vector<vector<int>> dist(H, vector<int>(W, -1));
        queue<pair<int, int>> que;
        que.push(make_pair(sx, sy));
        dist[sy][sx] = 0;
        bool found = false;
        while (!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= W || ny < 0 || ny >= H) {
                    continue;
                }
                if (field[ny][nx] == 'X') {
                    continue;
                }
                if (dist[ny][nx] != -1) {
                    continue;
                }
                dist[ny][nx] = dist[y][x] + 1;
                if (nx == gx && ny == gy) {
                    ans += dist[ny][nx];
                    found = true;
                    break;
                }
                que.push(make_pair(nx, ny));
            }
            if (found) {
                break;
            }
        }
    }
    cout << ans << endl;

    return 0;
}
