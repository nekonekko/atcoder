def main():
    N = int(input())
    D = list(map(int, input().split()))
    for i in range(N - 1):
        ans = 0
        for j in range(i, N - 1):
            ans += D[j]
            print(ans, end=' ')
        print()


if __name__ == "__main__":
    main()
