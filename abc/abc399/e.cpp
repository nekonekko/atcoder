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
    vector<int> par;   // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2
    vector<int> size;  // size[i]:iの木の頂点数

    UnionFind(int N) : par(N), size(N) {
        for (int i = 0; i < N; i++) {
            par[i] = i;
            size[i] = 1;  // 最初は全ての木の頂点数は1
        }
    }

    int root(
        int x) {  // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int x, int y) {    // xとyの木を併合
        int rx = root(x);         // xの根をrx
        int ry = root(y);         // yの根をry
        if (rx == ry) return;     // xとyの根が同じ(=同じ木にある)時はそのまま
        if (size[rx] < size[ry])  // rxの木の頂点数がryの木の頂点数より小さい時
            swap(rx, ry);         // rxとryを入れ替える
        par[rx] =
            ry;  // xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
        size[ry] += size[rx];  // yの木の頂点数を更新
    }

    bool same(int x, int y) {  // 2つのデータx, yが属する木が同じならtrueを返す
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }
};

int main() {
    int N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    // SとTが完全一致していれば0を出力
    if (S == T) {
        cout << 0 << endl;
        return 0;
    }

    UnionFind uf(26);

    vector<vector<int>> G(26);
    for (int i = 0; i < N; ++i) {
        G[S[i] - 'a'].push_back(T[i] - 'a');
        uf.unite(S[i] - 'a', T[i] - 'a');
    }
    // uniqueをとる
    for (int i = 0; i < 26; ++i) {
        sort(G[i].begin(), G[i].end());
        G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
    }

    // Ti!=TjかつSi==Sjとなるようなi, jが存在すれば不可能
    // つまり、出次数が2以上の頂点が存在すれば不可能
    for (int i = 0; i < 26; ++i) {
        if (G[i].size() > 1) {
            cout << -1 << endl;
            return 0;
        }
    }

    // 全ての連結成分において、その成分の全てで閉路が形成されている場合、不可能
    // ansを数えながら、不可能でないかどうかの判定を行う
    int ans = 0;
    bool exist_not_cycle = false;
    vector<bool> visited(26, false);
    for (int i = 0; i < 26; ++i) {
        if (visited[uf.root(i)]) continue;
        visited[uf.root(i)] = true;
        // iが含まれる連結成分に、閉路が含まれているか判定する
        // 閉路の長さも求める
        bool exist_cycle = false;
        vector<bool> visited2(26, false);
        int current_node = i;
        int next_node;
        visited2[current_node] = true;
        while (true) {
            if (G[current_node].size() == 0) {
                break;
            }
            next_node = G[current_node][0];
            if (visited2[next_node]) {
                exist_cycle = true;
                break;
            }
            visited2[next_node] = true;
            current_node = next_node;
        }
        // 閉路が存在しない場合、ansを計算してcontinue
        if (!exist_cycle) {
            exist_not_cycle = true;
            ans += uf.size[uf.root(i)] - 1;
            continue;
        }
        // 閉路が存在する場合、全頂点が閉路に含まれているかどうか調べる
        // そのために、閉路の長さを求める
        // next_nodeは閉路に含まれるため、next_nodeから出発してnext_nodeに戻るまでの長さを求める
        int cycle_length = 0;
        int cycle_start = next_node;
        current_node = next_node;
        while (true) {
            next_node = G[current_node][0];
            cycle_length++;
            if (next_node == cycle_start) {
                break;
            }
            current_node = next_node;
        }
        // 閉路の長さが1の場合
        if (cycle_length == 1) {
            if (uf.size[uf.root(i)] == 1) {
                continue;
            }
            ans += uf.size[uf.root(i)] - 1;
            exist_not_cycle = true;
            continue;
        }
        // 以下は閉路の長さが2以上の場合
        // 閉路の長さがその成分の頂点数と等しい場合
        if (cycle_length == uf.size[uf.root(i)]) {
            ans += uf.size[uf.root(i)] + 1;
            continue;
        }
        ans += uf.size[uf.root(i)];
        exist_not_cycle = true;
    }

    if (exist_not_cycle) {
        cout << ans << endl;
        return 0;
    }
    cout << -1 << endl;

    return 0;
}
