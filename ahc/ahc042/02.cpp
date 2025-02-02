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
    int N;
    cin >> N;
    vector<string> C(N);
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    vector<pair<char, int>> x_moves(N);
    // 左右に動かす
    for (int i = 0; i < N; i++) {
        vector<int> oni_x;
        vector<int> fuku_x;
        for (int j = 0; j < N; j++) {
            if (C[i][j] == 'x') {
                oni_x.push_back(j);
            } else {
                fuku_x.push_back(j);
            }
        }
        // 鬼がいない場合
        if (oni_x.size() == 0) {
            continue;
        }
        // 鬼しかいない場合
        if (fuku_x.size() == 0) {
            // 左に動かす場合
            if (oni_x[oni_x.size() - 1] + 1 < N - oni_x[0]) {
                for (int j = 0; j < oni_x[oni_x.size() - 1] + 1; j++) {
                    cout << "L " << i << endl;
                }
                C[i] = string(N, '.');
                x_moves[i] = make_pair('L', oni_x[oni_x.size() - 1] + 1);
                continue;
            }
            // 右に動かす場合
            for (int j = 0; j < N - oni_x[0]; j++) {
                cout << "R " << i << endl;
                C[i] = string(N, '.');
                x_moves[i] = make_pair('R', N - oni_x[0]);
            }
            continue;
        }
        // 鬼の左に福がいない場合
        if (oni_x[oni_x.size() - 1] < fuku_x[0]) {
            for (int j = 0; j < oni_x[oni_x.size() - 1] + 1; j++) {
                cout << "L " << i << endl;
            }
            C[i] = C[i].substr(oni_x[oni_x.size() - 1] + 1) +
                   string(N - (oni_x[oni_x.size() - 1] + 1), '.');
            x_moves[i] = make_pair('L', oni_x[oni_x.size() - 1] + 1);
            continue;
        }
        // 鬼の右に福がいない場合
        if (fuku_x[fuku_x.size() - 1] < oni_x[0]) {
            for (int j = 0; j < N - oni_x[0]; j++) {
                cout << "R " << i << endl;
            }
            C[i] = string(N - oni_x[0], '.') + C[i].substr(0, oni_x[0]);
            x_moves[i] = make_pair('R', N - oni_x[0]);
            continue;
        }
    }
    // 左右に動かした分を元に戻す
    for (int i = 0; i < N; i++) {
        if (x_moves[i].first == 'L') {
            for (int j = 0; j < x_moves[i].second; j++) {
                cout << "R " << i << endl;
            }
        } else if (x_moves[i].first == 'R') {
            for (int j = 0; j < x_moves[i].second; j++) {
                cout << "L " << i << endl;
            }
        }
    }
    // 上下に動かす
    for (int j = 0; j < N; j++) {
        vector<int> oni_y;
        vector<int> fuku_y;
        for (int i = 0; i < N; i++) {
            if (C[i][j] == 'x') {
                oni_y.push_back(i);
            } else {
                fuku_y.push_back(i);
            }
        }
        // 鬼がいない場合
        if (oni_y.size() == 0) {
            continue;
        }
        // 鬼しかいない場合
        if (fuku_y.size() == 0) {
            // 上に動かす場合
            if (oni_y[oni_y.size() - 1] + 1 < N - oni_y[0]) {
                for (int i = 0; i < oni_y[oni_y.size() - 1] + 1; i++) {
                    cout << "U " << j << endl;
                }
                for (int i = 0; i < N; i++) {
                    if (C[i][j] == 'x') {
                        C[i][j] = '.';
                    }
                }
                continue;
            }
            // 下に動かす場合
            for (int i = 0; i < N - oni_y[0]; i++) {
                cout << "D " << j << endl;
                for (int i = 0; i < N; i++) {
                    if (C[i][j] == 'x') {
                        C[i][j] = '.';
                    }
                }
            }
            continue;
        }
        // 鬼の上に福がいない場合
        if (oni_y[oni_y.size() - 1] < fuku_y[0]) {
            for (int i = 0; i < oni_y[oni_y.size() - 1] + 1; i++) {
                cout << "U " << j << endl;
            }
            for (int i = 0; i < N; i++) {
                if (C[i][j] == 'x') {
                    C[i][j] = '.';
                }
            }
            continue;
        }
        // 鬼の下に福がいない場合
        if (fuku_y[fuku_y.size() - 1] < oni_y[0]) {
            for (int i = 0; i < N - oni_y[0]; i++) {
                cout << "D " << j << endl;
            }
            for (int i = 0; i < N; i++) {
                if (C[i][j] == 'x') {
                    C[i][j] = '.';
                }
            }
            continue;
        }
    }

    return 0;
}
