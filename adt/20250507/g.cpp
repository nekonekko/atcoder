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
    vector<string> C(H);
    for (int i = 0; i < H; i++) {
        cin >> C[i];
    }
    vector<vector<int>> x(H, vector<int>(26, 0));
    vector<vector<int>> y(W, vector<int>(26, 0));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            x[i][C[i][j] - 'a']++;
            y[j][C[i][j] - 'a']++;
        }
    }
    int hc = H;
    int wc = W;
    vector<bool> row_exists(H, true);
    vector<bool> col_exists(W, true);
    for (int turn = 0; turn < H + W; turn++) {
        vector<pair<int, int>> delete_row;
        vector<pair<int, int>> delete_col;
        for (int i = 0; i < H; i++) {
            if (!row_exists[i]) continue;
            for (int c = 0; c < 26; c++) {
                if (x[i][c] == wc && wc >= 2) {
                    // cout << "Row " << i + 1 << " is eliminated." << endl;
                    delete_row.push_back({i, c});
                    break;
                }
            }
        }
        for (int j = 0; j < W; j++) {
            if (!col_exists[j]) continue;
            for (int c = 0; c < 26; c++) {
                if (y[j][c] == hc && hc >= 2) {
                    // cout << "Column " << j + 1 << " is eliminated." << endl;
                    delete_col.push_back({j, c});
                    break;
                }
            }
        }
        for (auto &p : delete_row) {
            int i = p.first, c = p.second;
            row_exists[i] = false;
            for (int j = 0; j < W; j++) {
                y[j][c]--;
            }
            hc--;
        }
        for (auto &p : delete_col) {
            int j = p.first, c = p.second;
            col_exists[j] = false;
            for (int i = 0; i < H; i++) {
                x[i][c]--;
            }
            wc--;
        }
        // cout << "Turn " << turn + 1 << ": hc = " << hc << ", wc = " << wc
        //      << endl;
    }

    cout << hc * wc << endl;

    return 0;
}
