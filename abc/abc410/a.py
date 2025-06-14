def main():
    N = int(input())
    A = list(map(int, input().split()))
    K = int(input())

    ans = 0
    for i in range(N):
        if A[i] >= K:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
