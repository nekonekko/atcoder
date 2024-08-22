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
using namespace std;

int count_tree_size(int current_node, vector< vector<int> > &edges, vector<bool> &visited) {
    queue<int> nodes_in_tree;
    int size = 1;
    visited.at(current_node) = true;
    nodes_in_tree.push(current_node);
    while (not nodes_in_tree.empty()) {
        int current_node = nodes_in_tree.front();
        nodes_in_tree.pop();
        for (int next_node : edges.at(current_node)) {
            if (visited.at(next_node)) {
                continue;
            }
            nodes_in_tree.push(next_node);
            visited.at(next_node) = true;
            size++;
        }
    }
    return size;
}

int main() {
    int n, u, v;
    cin >> n;
    vector< vector<int> > edges(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        u--;
        v--;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    vector<int> tree_size_list;
    for (int next_node : edges.at(0)) {
        vector<bool> visited(n, false);
        visited.at(0) = true;
        int current_size = count_tree_size(next_node, edges, visited);
        tree_size_list.push_back(current_size);
    }
    sort(tree_size_list.begin(), tree_size_list.end());
    int answer = 1;
    for (int i = 0; i < tree_size_list.size() - 1; i++) {
        answer += tree_size_list.at(i);
    }
    cout << answer << endl;
}
