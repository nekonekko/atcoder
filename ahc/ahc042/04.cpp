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
            C[i] = C[i].substr(oni_x[oni_x.size() - 1] + 1) +
                   string(oni_x[oni_x.size() - 1] + 1, '.');
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
            C[i] = string(N - oni_x[0], '.') + C[i].substr(0, oni_x[0]);
            // print_map(C);
            continue;
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
    }
    return move_log;
}

vector<string> move_others(int N, vector<string> &C) {
    vector<string> move_log;
    // print_map(C);
    // 残ったものの処理
    while (true) {
        bool flg = true;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (C[i][j] == 'x') {
                    flg = false;
                    int left_count = j + 1;
                    int right_count = N - j;
                    int up_count = i + 1;
                    int down_count = N - i;
                    // 福がいるかどうかチェック
                    for (int k = 0; k < j; k++) {
                        if (C[i][k] == 'o') {
                            left_count = 50;
                        }
                    }
                    for (int k = j + 1; k < N; k++) {
                        if (C[i][k] == 'o') {
                            right_count = 50;
                        }
                    }
                    for (int k = 0; k < i; k++) {
                        if (C[k][j] == 'o') {
                            up_count = 50;
                        }
                    }
                    for (int k = i + 1; k < N; k++) {
                        if (C[k][j] == 'o') {
                            down_count = 50;
                        }
                    }

                    // 全ての方向に福がいる場合
                    if (min({left_count, right_count, up_count, down_count}) ==
                        50) {
                        // 諦める
                        left_count = j + 1;
                        right_count = N - j;
                        up_count = i + 1;
                        down_count = N - i;
                    }
                    if (min({left_count, right_count, up_count, down_count}) ==
                        left_count) {
                        for (int k = 0; k < left_count; k++) {
                            move_log.push_back("L " + to_string(i));
                            // cout << "L " << i << endl;
                        }
                        C[i] =
                            string(left_count, '.') + C[i].substr(left_count);
                        // print_map(C);
                    } else if (min({left_count, right_count, up_count,
                                    down_count}) == right_count) {
                        for (int k = 0; k < right_count; k++) {
                            move_log.push_back("R " + to_string(i));
                            // cout << "R " << i << endl;
                        }
                        C[i] = C[i].substr(0, N - right_count) +
                               string(right_count, '.');
                        // print_map(C);
                    } else if (min({left_count, right_count, up_count,
                                    down_count}) == up_count) {
                        for (int k = 0; k < up_count; k++) {
                            move_log.push_back("U " + to_string(j));
                            // cout << "U " << j << endl;
                        }
                        for (int k = 0; k < up_count; k++) {
                            if (k + up_count < N) {
                                C[k][j] = C[k + up_count][j];
                            } else {
                                C[k][j] = '.';
                            }
                        }
                        for (int k = up_count; k < N; k++) {
                            C[k][j] = '.';
                        }
                        // print_map(C);
                    } else {
                        for (int k = 0; k < down_count; k++) {
                            move_log.push_back("D " + to_string(j));
                            // cout << "D " << j << endl;
                        }
                        for (int k = N - 1; k >= N - down_count; k--) {
                            if (k - (N - down_count) >= 0) {
                                C[k][j] = C[k - (N - down_count)][j];
                            } else {
                                C[k][j] = '.';
                            }
                        }
                        for (int k = 0; k < down_count; k++) {
                            C[k][j] = '.';
                        }
                        // print_map(C);
                    }
                }
            }
        }
        if (flg) {
            break;
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
    vector<string> move_log_first_xothers = move_others(N, C);

    for (auto &s : move_log_first_xx) {
        cout << s << endl;
    }
    for (auto &s : move_log_first_xy) {
        cout << s << endl;
    }
    for (auto &s : move_log_first_xothers) {
        cout << s << endl;
    }

    // ofs.close();
    // cout.rdbuf(last);
    return 0;
}
