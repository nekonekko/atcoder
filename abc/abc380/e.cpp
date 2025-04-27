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

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> colors(N);
    vector<int> color_count(N, 1);
    for (int i = 0; i < N; ++i) {
        colors[i] = i;
    }

    UnionFind uf(N);
    for (int i = 0; i < Q; ++i) {
        int t;
        cin >> t;
        if (t == 2) {
            int c;
            cin >> c;
            c--;
            cout << color_count[c] << endl;
            continue;
        }
        int x, c;
        cin >> x >> c;
        x--;
        c--;
        auto [l, r] = uf.get_range(x);
        color_count[colors[uf.root(x)]] -= r - l + 1;
        colors[uf.root(x)] = c;
        color_count[c] += r - l + 1;
        // 左側が同じ色だったらunite
        if (l > 0 && colors[uf.root(l - 1)] == c) {
            uf.unite(x, l - 1);
        }
        // 右側が同じ色だったらunite
        if (r < N - 1 && colors[uf.root(r + 1)] == c) {
            uf.unite(x, r + 1);
        }
    }

    return 0;
}
