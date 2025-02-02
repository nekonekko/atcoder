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
                }
                C[i] = string(N, '.');
                continue;
            }
            // 右に動かす場合
            for (int j = 0; j < N - oni_x[0]; j++) {
                move_log.push_back("R " + to_string(i));
            }
            C[i] = string(N, '.');
            continue;
        }
        // 福と鬼両方がいる場合
        // 福の左に鬼がいる場合
        int oni_left_fuku = -1;
        for (int j = 0; j < fuku_x[0]; j++) {
            if (C[i][j] == 'x') {
                oni_left_fuku = j;
            }
        }
        int oni_right_fuku = -1;
        for (int j = fuku_x[fuku_x.size() - 1] + 1; j < N; j++) {
            if (C[i][j] == 'x') {
                oni_right_fuku = j;
                break;
            }
        }
        bool oni_between_fuku = false;
        for (int j = fuku_x[0] + 1; j < fuku_x[fuku_x.size() - 1]; j++) {
            if (C[i][j] == 'x') {
                oni_between_fuku = true;
                break;
            }
        }
        if (oni_left_fuku != -1) {
            // 左に動かす
            for (int j = 0; j < oni_left_fuku + 1; j++) {
                move_log.push_back("L " + to_string(i));
                C[i][j] = '.';
            }
            // 福のいる列に鬼がいるか確認
            bool exist_oni = false;
            for (int k = 0; k < fuku_x.size(); k++) {
                for (int ii = 0; ii < N; ii++) {
                    if (C[ii][fuku_x[k] - (oni_left_fuku + 1)] == 'x') {
                        exist_oni = true;
                        break;
                    }
                }
                if (exist_oni) {
                    break;
                }
            }
            // 次の場合、動かした分戻す
            // 右に鬼がいる場合
            // 福のいる列に鬼がいる場合
            // 福の間に鬼が挟まれている場合
            if (oni_right_fuku != -1 || exist_oni || oni_between_fuku) {
                for (int j = 0; j < oni_left_fuku + 1; j++) {
                    move_log.push_back("R " + to_string(i));
                }
            }
        }
        // 福の右に鬼がいる場合
        if (oni_right_fuku != -1) {
            // 右に動かす
            for (int j = 0; j < N - oni_right_fuku; j++) {
                move_log.push_back("R " + to_string(i));
                C[i][N - j - 1] = '.';
            }
            // 福のいる列に鬼がいるか確認
            bool exist_oni = false;
            for (int k = 0; k < fuku_x.size(); k++) {
                for (int ii = 0; ii < N; ii++) {
                    if (C[ii][fuku_x[k] + (N - oni_right_fuku)] == 'x') {
                        exist_oni = true;
                        break;
                    }
                }
                if (exist_oni) {
                    break;
                }
            }
            // 次の場合、動かした分戻す
            // 福のいる列に鬼がいる場合
            // 福の間に鬼が挟まれている場合
            if (exist_oni || oni_between_fuku) {
                for (int j = 0; j < N - oni_right_fuku; j++) {
                    move_log.push_back("L " + to_string(i));
                }
            }
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
                }
                for (int i = 0; i < N; i++) {
                    C[i][j] = '.';
                }
                continue;
            }
            // 下に動かす場合
            for (int i = 0; i < N - oni_y[0]; i++) {
                move_log.push_back("D " + to_string(j));
            }
            for (int i = 0; i < N; i++) {
                C[i][j] = '.';
            }
            continue;
        }
        // 福と鬼両方がいる場合
        // 福の上に鬼がいる場合
        int oni_up_fuku = -1;
        for (int i = 0; i < fuku_y[0]; i++) {
            if (C[i][j] == 'x') {
                oni_up_fuku = i;
            }
        }
        int oni_down_fuku = -1;
        for (int i = fuku_y[fuku_y.size() - 1] + 1; i < N; i++) {
            if (C[i][j] == 'x') {
                oni_down_fuku = i;
                break;
            }
        }
        if (oni_up_fuku != -1) {
            // 上に動かす
            for (int i = 0; i < oni_up_fuku + 1; i++) {
                move_log.push_back("U " + to_string(j));
                // C[i][j] = '.';
            }
            // 福の下に鬼がいる場合、動かした分戻す
            if (oni_down_fuku != -1) {
                for (int i = 0; i < oni_up_fuku + 1; i++) {
                    move_log.push_back("D " + to_string(j));
                }
            }
        }
        // 福の下に鬼がいる場合
        if (oni_down_fuku != -1) {
            // 下に動かす
            for (int i = 0; i < N - oni_down_fuku; i++) {
                move_log.push_back("D " + to_string(j));
                // C[N - i - 1][j] = '.';
            }
            // // 動かした分戻す
            // for (int i = 0; i < N - oni_down_fuku; i++) {
            //     move_log.push_back("U " + to_string(j));
            // }
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

    vector<string> move_log_first_xx = move_x(N, C);
    vector<string> move_log_first_xy = move_y(N, C);

    for (auto &s : move_log_first_xx) {
        cout << s << endl;
    }
    for (auto &s : move_log_first_xy) {
        cout << s << endl;
    }
    return 0;
}
