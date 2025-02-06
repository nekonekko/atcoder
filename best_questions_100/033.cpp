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

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    vector<vector<int>> dist(H, vector<int>(W, -1));
    queue<pair<int, int>> que;
    que.push(make_pair(0, 0));
    dist[0][0] = 0;
    while (!que.empty()) {
        int x, y;
        tie(x, y) = que.front();
        que.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) {
                continue;
            }
            if (S[nx][ny] == '#') {
                continue;
            }
            if (dist[nx][ny] != -1) {
                continue;
            }
            dist[nx][ny] = dist[x][y] + 1;
            que.push(make_pair(nx, ny));
        }
    }

    if (dist[H - 1][W - 1] == -1) {
        cout << -1 << endl;
    } else {
        int ans = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (S[i][j] == '.') {
                    ans++;
                }
            }
        }
        ans -= dist[H - 1][W - 1] + 1;
        cout << ans << endl;
    }

    return 0;
}
