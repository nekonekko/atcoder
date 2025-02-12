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

struct UnionFind {
    vector<int> par;  // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2

    UnionFind(int N) : par(N) {  // 最初は全てが根であるとして初期化
        for (int i = 0; i < N; i++) par[i] = i;
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
        par[rx] =
            ry;  // xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
    }

    bool same(int x, int y) {  // 2つのデータx, yが属する木が同じならtrueを返す
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }
};

int main() {
    int N, M;
    cin >> N >> M;

    vector<tuple<int, int, int>> circuit_edges;
    UnionFind tree(N);

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if (tree.same(a, b)) {
            circuit_edges.push_back(make_tuple(i, a, b));
            continue;
        }
        tree.unite(a, b);
    }

    vector<vector<tuple<int, int, int>>> closed_circuit(N);

    for (auto [edge_id, a, b] : circuit_edges) {
        closed_circuit[tree.root(a)].push_back(make_tuple(edge_id, a, b));
    }

    // for (int i = 0; i < N; i++) {
    //     cout << "group " << i << ": "
    //          << "closed circuit: " << closed_circuit[i].size() << endl;
    //     for (auto [edge_id, from, to] : closed_circuit[i]) {
    //         cout << edge_id << " " << from << " " << to << endl;
    //     }
    // }

    vector<pair<int, int>> closed_circuit_num;
    for (int i = 0; i < N; i++) {
        if (tree.root(i) != i) continue;
        closed_circuit_num.push_back(make_pair(closed_circuit[i].size(), i));
    }
    // 閉路が多い順にソート
    sort(closed_circuit_num.begin(), closed_circuit_num.end(),
         greater<pair<int, int>>());

    cout << closed_circuit_num.size() - 1 << endl;

    // 閉路が2番目に多いグループから順に見ていく
    int from_group_idx = 0;
    int circuit_idx = 0;
    for (int i = 1; i < closed_circuit_num.size(); i++) {
        int from_group_root = closed_circuit_num[from_group_idx].second;

        int to_group_root = closed_circuit_num[i].second;

        auto current_circuit = closed_circuit[from_group_root][circuit_idx];
        int edge_id = get<0>(current_circuit);
        int from_original = get<1>(current_circuit);

        cout << edge_id + 1 << " " << from_original + 1 << " "
             << to_group_root + 1 << endl;

        circuit_idx++;
        if (circuit_idx == closed_circuit[from_group_root].size()) {
            circuit_idx = 0;
            from_group_idx++;
        }
    }

    return 0;
}
