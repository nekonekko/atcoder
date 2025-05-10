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

// from: https://algo-logic.info/trie-tree/
/* Trie 木： 文字の種類(char_size)、int型で0に対応する文字(base)
    insert(word): 単語 word を Trie 木に挿入する
    search(word): 単語 word が Trie 木にあるか判定する
    start_with(prefix):  prefix が一致する単語が Trie 木にあるか判定する
    delete_word(word): 単語 word を Trie 木から削除する
    include(word): 単語 word が Trie 木にあるか判定する
    count(): 挿入した単語の数を返す
    size(): Trie 木の頂点数を返す
    計算量：insert, search ともに O(M)（Mは単語の長さ）
*/
template <int char_size, int base>
struct Trie {
    struct Node {            // 頂点を表す構造体
        vector<int> next;    // 子の頂点番号を格納。存在しなければ-1
        vector<int> accept;  // 末端がこの頂点になる単語の word_id を保存
        bool is_deleted;
        int c;       // base からの間隔をint型で表現したもの
        int common;  // いくつの単語がこの頂点を共有しているか
        Node(int c_) : is_deleted(false), c(c_), common(0) {
            next.assign(char_size, -1);
        }
    };

    vector<Node> nodes;  // trie 木本体
    int root;
    Trie() : root(0) { nodes.push_back(Node(root)); }

    // 単語の挿入
    void insert(const string &word, int word_id) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ追加
                next_id = (int)nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.push_back(word_id);
    }
    void insert(const string &word) { insert(word, nodes[0].common); }

    // 単語とprefixの検索
    bool search(const string &word, bool prefix = false, bool include = false) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ終了
                if (include && i > 0 && nodes[node_id].accept.size() > 0) {
                    return true;
                }
                return false;
            }
            if (include && nodes[next_id].accept.size() > 0) {
                return true;
            }
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;
    }

    // prefix を持つ単語が存在するかの検索
    bool start_with(const string &prefix) {
        return search(prefix, true, false);
    }

    bool include(const string &word) { return search(word, false, true); }

    // word で始まる単語を全削除
    void delete_word(const string &word) {
        int node_id = 0;
        vector<int> remain_ids;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ終了
                return;
            }
            remain_ids.push_back(node_id);
            node_id = next_id;
        }
        // cout << "node_id: " << node_id << endl;
        // cout << "common: " << nodes[node_id].common << endl;
        // cout << "accept: " << nodes[node_id].accept.size() << endl;
        // for (auto accept_id : nodes[node_id].accept) {
        //     cout << "accept_id: " << accept_id << endl;
        // }
        int delete_words = nodes[node_id].common;
        // cout << "delete_words: " << delete_words << endl;
        // これより前のノードの common を減らす
        for (auto id : remain_ids) {
            nodes[id].common -= delete_words;
        }
        // 1つ前の Node の next から削除
        nodes[remain_ids.back()].next[(int)(word[word.size() - 1] - base)] = -1;
        // これから先の node の common をゼロに、is_deleted を true にする
        stack<int> stk;
        stk.push(node_id);
        while (stk.size() > 0) {
            int id = stk.top();
            stk.pop();
            nodes[id].common = 0;
            nodes[id].is_deleted = true;
            for (int i = 0; i < char_size; i++) {
                if (nodes[id].next[i] != -1) {
                    stk.push(nodes[id].next[i]);
                }
            }
        }
    }

    // 挿入した単語の数
    int count() const { return (nodes[0].common); }
    // Trie木のノード数
    int size() const { return ((int)nodes.size()); }
};

int main() {
    int Q;
    cin >> Q;

    vector<int> T(Q);
    vector<string> S(Q);
    for (int i = 0; i < Q; i++) {
        cin >> T[i] >> S[i];
    }

    Trie<26, 'a'> trieS;
    Trie<26, 'a'> trieT;
    for (int i = 0; i < Q; i++) {
        if (T[i] == 1) {
            trieS.insert(S[i]);
            if (!trieT.start_with(S[i])) {
                // cout << "not start_with" << endl;
                cout << trieT.count() << endl;
                continue;
            }
            // trieT から S[i] を削除
            // cout << "delete" << endl;
            trieT.delete_word(S[i]);
            cout << trieT.count() << endl;
            continue;
        }
        if (trieS.include(S[i])) {
            // cout << "include" << endl;
            cout << trieT.count() << endl;
            continue;
        }
        // cout << "not include" << endl;
        trieT.insert(S[i]);
        cout << trieT.count() << endl;
    }

    return 0;
}
