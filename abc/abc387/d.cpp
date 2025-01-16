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
#include <vector>
#include <tuple>

using namespace std;

struct Elem {
    int x, y, cnt, before_direction; // before_direction: 0 縦, 1 横
    Elem(int x, int y, int cnt, int before_direction)
        : x(x), y(y), cnt(cnt), before_direction(before_direction) {}
};

bool can_move(int x, int y, int H, int W, const vector< vector<char> >& grid) {
    if (x < 0 || x >= H || y < 0 || y >= W) return false;
    if (grid[x][y] == '#') return false;
    return true;
}

int main() {
    int H, W;
    cin >> H >> W;

    vector< vector<char> > grid(H, vector<char>(W));
    vector<int> start(2), goal(2);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                start[0] = int(i);
                start[1] = int(j);
            } else if (grid[i][j] == 'G') {
                goal[0] = int(i);
                goal[1] = int(j);
            }
        }
    }
    
    int dx_list[4] = {1, 0, -1, 0}; // x方向 (H方向)
    int dy_list[4] = {0, 1, 0, -1}; // y方向 (W方向)

    vector< vector<int> > dist_vertical(H, vector<int>(W, -1));
    vector< vector<int> > dist_horizontal(H, vector<int>(W, -1));

    queue<Elem> q;
    q.push(Elem(start[0], start[1], 0, 0)); // 初期位置から縦方向の移動
    q.push(Elem(start[0], start[1], 0, 1)); // 初期位置から横方向の移動

    while (!q.empty()) {
        Elem elem = q.front();
        q.pop();

        if (elem.before_direction == 0) {
            // 前の移動が縦の場合
            if (dist_vertical[elem.x][elem.y] != -1) continue;
            dist_vertical[elem.x][elem.y] = elem.cnt;
        } else {
            // 前の移動が横の場合
            if (dist_horizontal[elem.x][elem.y] != -1) continue;
            dist_horizontal[elem.x][elem.y] = elem.cnt;
        }

        for (int i = 0; i < 4; ++i) {
            if (elem.before_direction == (i % 2)) continue; // 前と同じ方向の移動はスキップ

            int nx = elem.x + dx_list[i];
            int ny = elem.y + dy_list[i];

            if (!can_move(nx, ny, H, W, grid)) continue;

            if (nx == goal[0] && ny == goal[1]) {
                cout << elem.cnt + 1 << endl;
                return 0;
            }

            q.push(Elem(nx, ny, elem.cnt + 1, i % 2));
        }
    }

    cout << -1 << endl;
    return 0;
}
