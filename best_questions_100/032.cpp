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
    while (true) {
        int W, H;
        cin >> W >> H;

        if (W == 0 && H == 0) {
            break;
        }

        vector<vector<int>> kabe_tate(H, vector<int>(W - 1));
        vector<vector<int>> kabe_yoko(H - 1, vector<int>(W));
        for (int i = 0; i < 2 * H - 1; i++) {
            if (i % 2 == 0) {
                for (int j = 0; j < W - 1; j++) {
                    cin >> kabe_tate[i / 2][j];
                }
            } else {
                for (int j = 0; j < W; j++) {
                    cin >> kabe_yoko[i / 2][j];
                }
            }
        }

        vector<vector<int>> dist(H, vector<int>(W, 0));
        queue<pair<int, int>> que;
        que.push({0, 0});
        dist[0][0] = 1;
        while (!que.empty()) {
            auto [x, y] = que.front();
            que.pop();
            // 上に移動
            if (y > 0 && dist[y - 1][x] == 0) {
                if (kabe_yoko[y - 1][x] == 0) {
                    dist[y - 1][x] = dist[y][x] + 1;
                    que.push({x, y - 1});
                }
            }
            // 下に移動
            if (y < H - 1 && dist[y + 1][x] == 0) {
                if (kabe_yoko[y][x] == 0) {
                    dist[y + 1][x] = dist[y][x] + 1;
                    que.push({x, y + 1});
                }
            }
            // 左に移動
            if (x > 0 && dist[y][x - 1] == 0) {
                if (kabe_tate[y][x - 1] == 0) {
                    dist[y][x - 1] = dist[y][x] + 1;
                    que.push({x - 1, y});
                }
            }
            // 右に移動
            if (x < W - 1 && dist[y][x + 1] == 0) {
                if (kabe_tate[y][x] == 0) {
                    dist[y][x + 1] = dist[y][x] + 1;
                    que.push({x + 1, y});
                }
            }
        }

        cout << dist[H - 1][W - 1] << endl;
    }

    return 0;
}
