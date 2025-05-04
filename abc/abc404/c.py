def main():
    N, M = map(int, input().split())
    G = [[] for _ in range(N)]
    for _ in range(M):
        a, b = map(int, input().split())
        G[a - 1].append(b - 1)
        G[b - 1].append(a - 1)

    # 字数チェック
    for i in range(N):
        if len(G[i]) != 2:
            print("No")
            return

    # 連結チェック
    visited = [False] * N
    stack = [0]
    while stack:
        v = stack.pop()
        visited[v] = True
        for nv in G[v]:
            if not visited[nv]:
                stack.append(nv)
    for i in range(N):
        if not visited[i]:
            print("No")
            return

    print("Yes")


if __name__ == "__main__":
    main()
