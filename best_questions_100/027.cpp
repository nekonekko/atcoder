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

int dfs(vector<vector<int>> &field, vector<vector<bool>> &visited,
        vector<int> &dx, vector<int> &dy, int x, int y, int N, int M) {
    int res = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) {
            continue;
        }
        if (field[nx][ny] == 0 || visited[nx][ny]) {
            continue;
        }
        visited[nx][ny] = true;
        res = max(res, dfs(field, visited, dx, dy, nx, ny, N, M));
        visited[nx][ny] = false;
    }
    res++;
    return res;
}

int main() {
    int M, N;
    cin >> M >> N;
    vector<vector<int>> field(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> field[i][j];
        }
    }

    vector<int> dx = {1, 0, -1, 0};
    vector<int> dy = {0, 1, 0, -1};
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field[i][j] == 0) {
                continue;
            }
            vector<vector<bool>> visited(N, vector<bool>(M, false));
            visited[i][j] = true;
            int res = dfs(field, visited, dx, dy, i, j, N, M);
            ans = max(ans, res);
        }
    }
    cout << ans << endl;

    return 0;
}
