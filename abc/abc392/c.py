def main():
    N = int(input())
    P = list(map(int, input().split()))
    Q = list(map(int, input().split()))
    ans = [-1 for _ in range(N)]
    for i in range(N):
        ans[Q[i] - 1] = Q[P[i] - 1]
    for i in range(N):
        print(ans[i], end=" ")
    print("")


if __name__ == "__main__":
    main()
