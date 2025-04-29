def main():
    N, M, Q = map(int, input().split())
    permissions = [set() for _ in range(N)]
    all_permissions = [False for _ in range(N)]
    for i in range(Q):
        query = list(map(int, input().split()))
        if query[0] == 1:
            x, y = query[1] - 1, query[2] - 1
            permissions[x].add(y)
        elif query[0] == 2:
            x = query[1] - 1
            all_permissions[x] = True
        else:
            x, y = query[1] - 1, query[2] - 1
            if all_permissions[x] or y in permissions[x]:
                print("Yes")
            else:
                print("No")


if __name__ == "__main__":
    main()
