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

struct UnionFind {
    vector<int> par;   // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2
    vector<int> size;  // size[i]:iの木のサイズ
    vector<pair<int, int>> range;  // range[root(i)]:iの木の範囲

    UnionFind(int N)
        : par(N), size(N), range(N) {  // 最初は全てが根であるとして初期化
        for (int i = 0; i < N; i++) {
            par[i] = i;
            size[i] = 1;
            range[i] = {i, i};  // 各木の範囲は1
        }  // 各木のサイズは1
    }

    int root(
        int x) {  // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int x, int y) {  // xとyの木を併合
        int rx = root(x);       // xの根をrx
        int ry = root(y);       // yの根をry
        if (rx == ry) return;   // xとyの根が同じ(=同じ木にある)時はそのまま
        if (size[rx] <
            size[ry]) {            // rxの木のサイズがryの木のサイズより小さい時
            par[rx] = ry;          // rxの親をryにする
            size[ry] += size[rx];  // ryの木のサイズを更新
            range[ry].first =
                min(range[rx].first, range[ry].first);  // ryの木の範囲を更新
            range[ry].second =
                max(range[rx].second, range[ry].second);  // ryの木の範囲を更新
        } else {
            par[ry] = rx;          // ryの親をrxにする
            size[rx] += size[ry];  // rxの木のサイズを更新
            range[rx].first =
                min(range[rx].first, range[ry].first);  // rxの木の範囲を更新
            range[rx].second =
                max(range[rx].second, range[ry].second);  // rxの木の範囲を更新
        }
    }

    int get_size(int x) {  // データxが属する木のサイズを返す
        return size[root(x)];
    }

    pair<int, int> get_range(int x) {  // データxが属する木の範囲を返す
        return range[root(x)];
    }

    bool same(int x, int y) {  // 2つのデータx, yが属する木が同じならtrueを返す
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }
};

bool dfs(int v, const vector<vector<int>>& G, vector<long long>& node_type,
         vector<bool>& visited) {
    visited[v] = true;

    for (int to : G[v]) {
        if (visited[to]) {
            // If we revisit a node, it means there's a cycle, which is invalid
            continue;
        }
        if (!dfs(to, G, node_type, visited)) {
            return false;  // If any DFS call fails, return false
        }
    }

    int cnt_type_one_child = 0;
    for (int to : G[v]) {
        if (node_type[to] == 1) {
            cnt_type_one_child++;
        }
    }
    if (cnt_type_one_child > 1) {
        // If a node has more than one child of type 1, it's invalid
        return false;
    }
    if (cnt_type_one_child == 1) {
        // If it has exactly one child of type 1, set this node to type 2
        node_type[v] = 2;
    } else {
        // If it has no children of type 1, set this node to type 1
        node_type[v] = 1;
    }

    return true;
}

int main() {
    int H, W;
    cin >> H >> W;
    vector<vector<long long>> A(H, vector<long long>(W));
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            cin >> A[i][j];
        }
    }

    vector<int> possible_dominoes;
    possible_dominoes.push_back(0);
    const int vertical_domino = (1 << W) + 1;
    const int horizontal_domino = 3;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            int sz = possible_dominoes.size();
            for (int k = 0; k < sz; ++k) {
                int base_dominoes = possible_dominoes[k];
                if (i + 1 < H &&
                    !(base_dominoes & (vertical_domino << (i * W + j)))) {
                    int new_domino =
                        base_dominoes | (vertical_domino << (i * W + j));
                    possible_dominoes.push_back(new_domino);
                }
                if (j + 1 < W &&
                    !(base_dominoes & (horizontal_domino << (i * W + j)))) {
                    int new_domino =
                        base_dominoes | (horizontal_domino << (i * W + j));
                    possible_dominoes.push_back(new_domino);
                }
            }
        }
    }

    long long ans = 0;
    for (auto dominoes : possible_dominoes) {
        long long current_xor = 0;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (dominoes & (1 << (i * W + j))) {
                    continue;
                }
                current_xor ^= A[i][j];
            }
        }
        ans = max(ans, current_xor);
    }
    cout << ans << endl;
    return 0;
}
