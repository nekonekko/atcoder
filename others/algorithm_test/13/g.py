def main():
    INF = 10**18

    N = int(input())
    A = list(map(int, input().split()))

    accum = [0] * (N + 1)
    for i in range(N):
        accum[i + 1] = accum[i] + A[i]

    min_l = accum[0]
    ans = -INF
    for i in range(1, N):
        ans = max(ans, accum[i] - min_l)
        min_l = min(min_l, accum[i])
    ans = max(ans, accum[N] - min_l)
    print(ans)


if __name__ == "__main__":
    main()
