from collections import defaultdict


def main():
    N, D = map(int, input().split())
    A = list(map(int, input().split()))

    if D == 0:
        a_cnt = defaultdict(int)
        for i in range(N):
            a_cnt[A[i]] += 1
        ans = 0
        for k, v in a_cnt.items():
            ans += v - 1
        print(ans)
        return

    max_a = max(A)
    exist_num = defaultdict(lambda: int())
    for i in range(N):
        # print(f"A[i]: {A[i]}, i%D: {i % D}, A[i] // D: {A[i] // D}")
        exist_num[A[i]] += 1

    # print(exist_num)

    dp = [[[int(10**9) for _ in range(2)] for _ in range(2)] for _ in range(max_a + 1)]
    # dp[i][j][k] = i番目まで連続しないような要素削除数の最小値
    # j: i番目を消すかどうか
    # k: i-1番目を消すかどうか
    ans = 0
    for i in range(max_a + 1):
        if exist_num[i] == 0:
            continue
        # 前があるかどうか
        if i - D >= 0 and exist_num[i - D] > 0:
            # 前がある
            dp[i][0][1] = min(dp[i - D][1][0], dp[i - D][1][1])
            dp[i][1][0] = dp[i - D][0][1] + exist_num[i]
            dp[i][1][1] = min(dp[i - D][1][0], dp[i - D][1][1]) + exist_num[i]
        else:
            # 前がない
            # 前のコストを0とみなす
            dp[i][0][1] = 0
            dp[i][1][0] = exist_num[i]
            dp[i][1][1] = exist_num[i]

        # 後があるかどうか
        if i + D <= max_a and exist_num[i + D] > 0:
            # 後がある
            continue
        # 後がない場合
        # ans に加算する
        ans += min(dp[i][0][1], dp[i][1][0], dp[i][1][1])

    print(ans)


if __name__ == "__main__":
    main()
