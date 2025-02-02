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

void print_map(vector<string> &C) {
    cout << "  ";
    for (int i = 0; i < C.size(); i++) {
        cout << i % 10;
    }
    cout << endl;
    for (int i = 0; i < C.size(); i++) {
        if (i < 10) {
            cout << " ";
        }
        cout << i;
        cout << C[i] << endl;
    }
}

vector<string> move_x(int N, vector<string> &C) {
    vector<string> move_log;
    vector<pair<char, int>> x_moves(N);

    // 左右に動かす
    for (int i = 0; i < N; i++) {
        vector<int> oni_x;
        vector<int> fuku_x;
        for (int j = 0; j < N; j++) {
            if (C[i][j] == 'x') {
                oni_x.push_back(j);
            } else if (C[i][j] == 'o') {
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
                    move_log.push_back("L " + to_string(i));
                    // cout << "L " << i << endl;
                    // cnt++;
                }
                C[i] = string(N, '.');
                // x_moves[i] = make_pair('L', oni_x[oni_x.size() - 1] + 1);
                // print_map(C);
                continue;
            }
            // 右に動かす場合
            for (int j = 0; j < N - oni_x[0]; j++) {
                move_log.push_back("R " + to_string(i));
                // cout << "R " << i << endl;
                // cnt++;
            }
            C[i] = string(N, '.');
            // x_moves[i] = make_pair('R', N - oni_x[0]);
            // print_map(C);
            continue;
        }
        // 鬼の左に福がいない場合
        if (oni_x[oni_x.size() - 1] < fuku_x[0]) {
            for (int j = 0; j < oni_x[oni_x.size() - 1] + 1; j++) {
                move_log.push_back("L " + to_string(i));
                // cout << "L " << i << endl;
                // cnt++;
            }
            for (int j = 0; j < N; j++) {
                if (C[i][j] == 'x') {
                    C[i][j] = '.';
                }
            }
            // C[i] = C[i].substr(oni_x[oni_x.size() - 1] + 1) +
            //        string(oni_x[oni_x.size() - 1] + 1, '.');
            x_moves[i] = make_pair('L', oni_x[oni_x.size() - 1] + 1);
            // print_map(C);
            continue;
        }
        // 鬼の右に福がいない場合
        if (fuku_x[fuku_x.size() - 1] < oni_x[0]) {
            for (int j = 0; j < N - oni_x[0]; j++) {
                move_log.push_back("R " + to_string(i));
                // cout << "R " << i << endl;
                // cnt++;
            }
            for (int j = 0; j < N; j++) {
                if (C[i][j] == 'x') {
                    C[i][j] = '.';
                }
            }
            // C[i] = string(N - oni_x[0], '.') + C[i].substr(0, oni_x[0]);
            x_moves[i] = make_pair('R', N - oni_x[0]);
            // print_map(C);
            continue;
        }
        // 鬼が福を挟んでいる場合
        // まず左に動かす
        for (int j = 0; j < fuku_x[0]; j++) {
            move_log.push_back("L " + to_string(i));
            // cout << "L " << i << endl;
            // cnt++;
        }
        // 動かした分戻す
        for (int j = 0; j < fuku_x[0]; j++) {
            move_log.push_back("R " + to_string(i));
            // cout << "R " << i << endl;
            // cnt++;
        }
        // 次に右に動かす
        for (int j = 0; j < N - fuku_x[fuku_x.size() - 1] - 1; j++) {
            move_log.push_back("R " + to_string(i));
            // cout << "R " << i << endl;
            // cnt++;
        }
        // 動かした分戻す
        for (int j = 0; j < N - fuku_x[fuku_x.size() - 1] - 1; j++) {
            move_log.push_back("L " + to_string(i));
            // cout << "L " << i << endl;
            // cnt++;
        }
    }
    // 左右に動かした分を元に戻す
    for (int i = 0; i < N; i++) {
        if (x_moves[i].first == 'L') {
            for (int j = 0; j < x_moves[i].second; j++) {
                move_log.push_back("R " + to_string(i));
                // cout << "R " << i << endl;
                // cnt++;
            }
            // C[i] = string(N - x_moves[i].second, '.') +
            //        C[i].substr(0, x_moves[i].second);
        } else if (x_moves[i].first == 'R') {
            for (int j = 0; j < x_moves[i].second; j++) {
                move_log.push_back("L " + to_string(i));
                // cout << "L " << i << endl;
                // cnt++;
            }
            // C[i] = C[i].substr(x_moves[i].second) +
            //        string(N - x_moves[i].second, '.');
        }
    }
    return move_log;
}

vector<string> move_y(int N, vector<string> &C) {
    vector<string> move_log;
    // 上下に動かす
    for (int j = 0; j < N; j++) {
        vector<int> oni_y;
        vector<int> fuku_y;
        for (int i = 0; i < N; i++) {
            if (C[i][j] == 'x') {
                oni_y.push_back(i);
            } else if (C[i][j] == 'o') {
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
                    move_log.push_back("U " + to_string(j));
                    // cout << "U " << j << endl;
                    // cnt++;
                }
                for (int i = 0; i < N; i++) {
                    C[i][j] = '.';
                }
                // print_map(C);
                continue;
            }
            // 下に動かす場合
            for (int i = 0; i < N - oni_y[0]; i++) {
                move_log.push_back("D " + to_string(j));
                // cout << "D " << j << endl;
                // cnt++;
            }
            for (int i = 0; i < N; i++) {
                C[i][j] = '.';
            }
            // print_map(C);
            continue;
        }
        // 鬼の上に福がいない場合
        if (oni_y[oni_y.size() - 1] < fuku_y[0]) {
            for (int i = 0; i < oni_y[oni_y.size() - 1] + 1; i++) {
                move_log.push_back("U " + to_string(j));
                // cout << "U " << j << endl;
                // cnt++;
            }
            for (int i = 0; i < oni_y[oni_y.size() - 1] + 1; i++) {
                if (i + oni_y[oni_y.size() - 1] + 1 < N) {
                    C[i][j] = C[i + oni_y[oni_y.size() - 1] + 1][j];
                } else {
                    C[i][j] = '.';
                }
            }
            for (int i = oni_y[oni_y.size() - 1] + 1; i < N; i++) {
                C[i][j] = '.';
            }
            // print_map(C);
            continue;
        }
        // 鬼の下に福がいない場合
        if (fuku_y[fuku_y.size() - 1] < oni_y[0]) {
            for (int i = 0; i < N - oni_y[0]; i++) {
                move_log.push_back("D " + to_string(j));
                // cout << "D " << j << endl;
                // cnt++;
            }
            for (int i = N - 1; i >= N - oni_y[0]; i--) {
                if (i - (N - oni_y[0]) >= 0) {
                    C[i][j] = C[i - (N - oni_y[0])][j];
                } else {
                    C[i][j] = '.';
                }
            }
            for (int i = 0; i < N - oni_y[0]; i++) {
                C[i][j] = '.';
            }
            // print_map(C);
            continue;
        }
        // 鬼が福を挟んでいる場合
        // まず上に動かす
        for (int i = 0; i < fuku_y[0]; i++) {
            move_log.push_back("U " + to_string(j));
            // cout << "U " << j << endl;
            // cnt++;
        }
        // 動かした分戻す
        for (int i = 0; i < fuku_y[0]; i++) {
            move_log.push_back("D " + to_string(j));
            // cout << "D " << j << endl;
            // cnt++;
        }
        // 次に下に動かす
        for (int i = 0; i < N - fuku_y[fuku_y.size() - 1] - 1; i++) {
            move_log.push_back("D " + to_string(j));
            // cout << "D " << j << endl;
            // cnt++;
        }
    }
    return move_log;
}

int main() {
    int N;
    cin >> N;
    vector<string> C(N);
    // vector<string> C2(N);
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    // copy(C.begin(), C.end(), C2.begin());

    // streambuf *last = cout.rdbuf();
    // ofstream ofs("test.txt", ios_base::out);
    // cout.rdbuf(ofs.rdbuf());

    // print_map(C);

    vector<string> move_log_first_xx = move_x(N, C);
    vector<string> move_log_first_xy = move_y(N, C);

    for (auto &s : move_log_first_xx) {
        cout << s << endl;
    }
    for (auto &s : move_log_first_xy) {
        cout << s << endl;
    }

    // ofs.close();
    // cout.rdbuf(last);
    return 0;
}
