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
    int R, C;
    cin >> R >> C;
    int sy, sx, gy, gx;
    cin >> sy >> sx >> gy >> gx;
    sy--, sx--, gy--, gx--;
    vector<string> c(R);
    for (int i = 0; i < R; i++) {
        cin >> c[i];
    }

    vector<int> dx = {1, 0, -1, 0};
    vector<int> dy = {0, 1, 0, -1};

    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int, int>> que;
    que.push(make_pair(sy, sx));
    dist[sy][sx] = 0;
    while (!que.empty()) {
        int y, x;
        tie(y, x) = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || ny >= R || nx < 0 || nx >= C) {
                continue;
            }
            if (c[ny][nx] == '#') {
                continue;
            }
            if (dist[ny][nx] != -1) {
                continue;
            }
            dist[ny][nx] = dist[y][x] + 1;
            que.push(make_pair(ny, nx));
        }
    }

    cout << dist[gy][gx] << endl;

    return 0;
}
