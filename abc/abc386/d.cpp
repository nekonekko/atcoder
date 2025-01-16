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
#include <vector>
#include <tuple>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<tuple<int, int>> white;
    vector<tuple<int, int>> black;
    for (int i = 0; i < M; ++i) {
        int x, y;
        char color;
        cin >> x >> y >> color;
        if (color == 'W') {
            white.push_back(make_tuple(x, y));
        } else {
            black.push_back(make_tuple(x, y));
        }
    }

    if (white.size() == 0 || black.size() == 0) {
        cout << "Yes" << endl;
        return 0;
    }

    sort(white.begin(), white.end());
    sort(black.begin(), black.end());

    int white_idx = 0;
    int min_white_y = get<1>(white[0]);
    for (auto b: black) {
        if (get<0>(b) < get<0>(white[0])) {
            continue;   
        }
        while (static_cast<size_t>(white_idx) + 1 < white.size() && get<0>(white[white_idx + 1]) <= get<0>(b)) {
            ++white_idx;
            min_white_y = min(min_white_y, get<1>(white[white_idx]));
        }
        if (min_white_y <= get<1>(b)) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}
