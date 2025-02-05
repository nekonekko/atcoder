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
        vector<vector<int>> field(H, vector<int>(W));
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin >> field[i][j];
            }
        }

        vector<vector<bool>> visited(H, vector<bool>(W, false));
        vector<int> dx = {1, 0, -1, 0};
        vector<int> dy = {0, 1, 0, -1};
        int ans = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (field[i][j] == 1 && !visited[i][j]) {
                    ans++;
                    queue<pair<int, int>> que;
                    que.push(make_pair(i, j));
                    visited[i][j] = true;
                    while (!que.empty()) {
                        pair<int, int> p = que.front();
                        que.pop();
                        for (int k = 0; k < 4; k++) {
                            for (int l = 0; l < 4; l++) {
                                if (dx[k] == 0 && dy[l] == 0) {
                                    continue;
                                }
                                int ni = p.first + dx[k];
                                int nj = p.second + dy[l];
                                if (ni >= 0 && ni < H && nj >= 0 && nj < W &&
                                    field[ni][nj] == 1 && !visited[ni][nj]) {
                                    que.push(make_pair(ni, nj));
                                    visited[ni][nj] = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
