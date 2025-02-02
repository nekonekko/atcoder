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
    int N, W;
    cin >> N >> W;
    // x: 0-indexed
    // y: 1-indexed
    vector<vector<int>> blocks(W, vector<int>());
    map<pair<int, int>, int> pos_to_block_id;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        blocks[x].push_back(y);
        pos_to_block_id[make_pair(x, y)] = i + 1;
    }

    int Q;
    cin >> Q;
    vector<int> T(Q), A(Q);
    for (int i = 0; i < Q; i++) {
        cin >> T[i] >> A[i];
    }

    for (int i = 0; i < W; i++) {
        sort(blocks[i].begin(), blocks[i].end());
    }
    int minimum_blocks = 1e9;
    for (int i = 0; i < W; i++) {
        minimum_blocks = min(minimum_blocks, int(blocks[i].size()));
    }
    map<int, int> disapper_time;
    for (int i = 0; i < minimum_blocks; i++) {
        int max_y = 0;
        for (int j = 0; j < W; j++) {
            max_y = max(max_y, blocks[j][i]);
        }
        for (int j = 0; j < W; j++) {
            disapper_time[pos_to_block_id[make_pair(j, blocks[j][i])]] = max_y;
        }
    }
    for (int i = 0; i < W; i++) {
        if (blocks[i].size() > minimum_blocks) {
            for (int j = minimum_blocks; j < blocks[i].size(); j++) {
                disapper_time[pos_to_block_id[make_pair(i, blocks[i][j])]] = -1;
            }
        }
    }

    // クエリに答える
    for (int i = 0; i < Q; i++) {
        if (disapper_time[A[i]] == -1) {
            cout << "Yes" << endl;
        } else if (disapper_time[A[i]] > T[i]) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
