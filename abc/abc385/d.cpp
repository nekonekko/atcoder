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

int get_lower_bound(vector<vector<int>> &sorted, long first_item, long second_item, int N) {
    int left = -1;
    int right = N;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (sorted[mid][0] < first_item || (sorted[mid][0] == first_item && sorted[mid][1] < second_item)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return right;
}

int get_upper_bound(vector<vector<int>> &sorted, long first_item, long second_item, int N) {
    int left = -1;
    int right = N;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (sorted[mid][0] < first_item || (sorted[mid][0] == first_item && sorted[mid][1] <= second_item)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return right;
}

int main() {
    int N, M;
    long Sx, Sy;
    cin >> N >> M >> Sx >> Sy;

    vector<int> X(N), Y(N);
    vector<char> D(M);
    vector<long> C(M);

    vector<vector<int>> sorted_by_x(N), sorted_by_y(N);

    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
        sorted_by_x[i] = {X[i], Y[i], i};
        sorted_by_y[i] = {Y[i], X[i], i};
    }
    sort(sorted_by_x.begin(), sorted_by_x.end());
    sort(sorted_by_y.begin(), sorted_by_y.end());

    for (int i = 0; i < M; i++) {
        cin >> D[i] >> C[i];
    }

    long x, y;
    x = Sx;
    y = Sy;
    vector<int> count_x(N + 1), count_y(N + 1);
    for (int i = 0; i < M; i++) {
        if (D[i] == 'U' or D[i] == 'D') {
            long miny, maxy;

            if (D[i] == 'U') {
                miny = y;
                maxy = y + C[i];
                y = y + C[i];
            } else {
                miny = y - C[i];
                maxy = y;
                y = y - C[i];
            }

            int min_idx = get_lower_bound(sorted_by_x, x, miny, N);
            int max_idx = get_upper_bound(sorted_by_x, x, maxy, N);

            count_y[min_idx] += 1;
            count_y[max_idx] -= 1;
        } else {
            long minx, maxx;

            if (D[i] == 'R') {
                minx = x;
                maxx = x + C[i];
                x = x + C[i];
            } else {
                minx = x - C[i];
                maxx = x;
                x = x - C[i];
            }

            int min_idx = get_lower_bound(sorted_by_y, y, minx, N);
            int max_idx = get_upper_bound(sorted_by_y, y, maxx, N);
            count_x[min_idx] += 1;
            count_x[max_idx] -= 1;
        }
    }

    for (int i = 0; i < N; i++) {
        count_x[i + 1] += count_x[i];
        count_y[i + 1] += count_y[i];
    }

    vector<bool> visited(N);
    for (int i = 0; i < N; i++) {
        if (count_x[i] > 0) {
            visited[sorted_by_y[i][2]] = true;
        }
        if (count_y[i] > 0) {
            visited[sorted_by_x[i][2]] = true;
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (visited[i]) {
            ans += 1;
        }
    }

    cout << x << " " << y << " " << ans << endl;

    return 0;
}
