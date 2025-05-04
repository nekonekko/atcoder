def main():
    INF = int(10**18)
    X, Y, Z = map(int, input().split())
    S = input()
    dp = [[INF for _ in range(2)] for _ in range(len(S))]
    if S[0] == "a":
        dp[0][0] = X
        dp[0][1] = Z + Y
    else:
        dp[0][0] = Y
        dp[0][1] = Z + X

    for i in range(1, len(S)):
        if S[i] == "a":
            dp[i][0] = min(dp[i - 1][0] + X, dp[i - 1][1] + Z + X)
            dp[i][1] = min(dp[i - 1][0] + Z + Y, dp[i - 1][1] + Y)
        else:
            dp[i][0] = min(dp[i - 1][0] + Y, dp[i - 1][1] + Z + Y)
            dp[i][1] = min(dp[i - 1][0] + Z + X, dp[i - 1][1] + X)

    print(min(dp[-1][0], dp[-1][1]))


if __name__ == "__main__":
    main()
