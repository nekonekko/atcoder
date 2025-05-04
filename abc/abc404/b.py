def main():
    N = int(input())
    S = []
    T = []
    for i in range(N):
        S.append(input())
    for i in range(N):
        T.append(input())

    # そのまま
    ans = int(1e9)
    cur = 0
    for i in range(N):
        for j in range(N):
            if S[i][j] != T[i][j]:
                cur += 1

    ans = min(ans, cur)
    # print(cur)

    # 90度回転
    cur = 1
    for i in range(N):
        for j in range(N):
            if S[i][j] != T[j][N - 1 - i]:
                cur += 1
    ans = min(ans, cur)
    # print(cur)

    # 180度回転
    cur = 2
    for i in range(N):
        for j in range(N):
            if S[i][j] != T[N - 1 - i][N - 1 - j]:
                cur += 1
    ans = min(ans, cur)
    # print(cur)

    # 270度回転
    cur = 3
    for i in range(N):
        for j in range(N):
            if S[i][j] != T[N - 1 - j][i]:
                cur += 1
    ans = min(ans, cur)
    # print(cur)

    print(ans)


if __name__ == "__main__":
    main()
