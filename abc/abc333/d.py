def count_tree_size(node, edges, visited):
    nodes_in_tree = [node]
    size = 1
    visited[node] = True
    while nodes_in_tree:
        current_node = nodes_in_tree.pop()
        for next_node in edges[current_node]:
            if visited[next_node]:
                continue
            nodes_in_tree.append(next_node)
            visited[next_node] = True
            size += 1
    return size


def main():
    n = int(input())
    edges = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        edges[u - 1].append(v - 1)
        edges[v - 1].append(u - 1)

    tree_size_list = []
    for next_node in edges[0]:
        visited = [False] * n
        visited[0] = True
        current_size = count_tree_size(next_node, edges, visited)
        tree_size_list.append(current_size)
    tree_size_list = sorted(tree_size_list)
    print(sum(tree_size_list[:-1]) + 1)


if __name__ == "__main__":
    main()
