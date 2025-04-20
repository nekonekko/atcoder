import bisect


def dfs_upper_left(x, y, A, upper_left, M, val):
    if x + y == len(A) - 1:
        upper_left[x].append(val % M)
        return
    dfs_upper_left(x + 1, y, A, upper_left, M, (val + A[x + 1][y]) % M)
    dfs_upper_left(x, y + 1, A, upper_left, M, (val + A[x][y + 1]) % M)


def dfs_lower_right(x, y, A, lower_right, M, val):
    if x + y == len(A) - 1:
        lower_right[x].append((val - A[x][len(A) - x - 1]) % M)
        return
    dfs_lower_right(x - 1, y, A, lower_right, M, (val + A[x - 1][y]) % M)
    dfs_lower_right(x, y - 1, A, lower_right, M, (val + A[x][y - 1]) % M)


def main():
    N, M = map(int, input().split())
    A = [list(map(int, input().split())) for _ in range(N)]
    for i in range(N):
        for j in range(N):
            A[i][j] = A[i][j] * 10 ** (2 * N - 1 - i - j - 1) % M

    # print(A)

    upper_left = [[] for _ in range(N)]
    lower_right = [[] for _ in range(N)]

    dfs_upper_left(0, 0, A, upper_left, M, A[0][0])
    dfs_lower_right(N - 1, N - 1, A, lower_right, M, A[N - 1][N - 1])

    for i in range(N):
        lower_right[i].sort()

    ans = 0
    for x in range(N):
        for i in range(len(upper_left[x])):
            # upper_left[x][i] + lower_right[x][j] < M
            upper_m = bisect.bisect_left(lower_right[x], M - upper_left[x][i])
            max_m = upper_m - 1
            if upper_m >= 0:
                ans = max(ans, (upper_left[x][i] + lower_right[x][max_m]) % M)
            ans = max(ans, (upper_left[x][i] + lower_right[x][-1]) % M)
    print(ans)

    # print(upper_left)
    # print(lower_right)


if __name__ == "__main__":
    main()
