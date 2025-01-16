def count_under_s(s):
    new_s = s[0]
    flg = False
    for ch in s[1:]:
        if int(ch) >= int(s[0]):
            flg = True
            new_s += str(int(s[0]) - 1)
        else:
            if flg:
                new_s += str(int(s[0]) - 1)
            else:
                new_s += ch
    s = new_s

    # ----------------------------
    # 一番左の桁がs[0]と等しい場合を DP で求める
    # dp[左からi桁目][i桁目の値][上限ちょうどかどうか]
    dp = [[[0 for _ in range(2)] for _ in range(10)] for _ in range(len(s))]
    dp[0][int(s[0])][1] = 1

    # 左からi桁目を更新
    for i in range(1, len(s)):
        # i桁目の値:j, i-1桁目の値:jj
        for j in range(int(s[0])):
            for jj in range(int(s[0]) + 1):
                dp[i][j][0] += dp[i - 1][jj][0]
                if jj == int(s[i - 1]):
                    if j == int(s[i]):
                        dp[i][j][1] += dp[i - 1][jj][1]
                    elif j < int(s[i]):
                        dp[i][j][0] += dp[i - 1][jj][1]

    count = 0
    for j in range(10):
        for k in range(2):
            count += dp[len(s) - 1][j][k]

    # ----------------------------
    # 一番左の桁がs[0]より小さい場合を数える
    for i in reversed(range(1, len(s) + 1)):
        for j in range(1, 10):
            if i == len(s) and j >= int(s[0]):
                break
            count += j ** (i - 1)

    return count


def main():
    L, R = map(int, input().split())
    L -= 1

    l_str = str(L)
    r_str = str(R)

    under_l = count_under_s(l_str)
    under_r = count_under_s(r_str)

    print(under_r - under_l)


if __name__ == "__main__":
    main()
