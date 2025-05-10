def main():
    N = int(input())
    A = list(map(int, input().split()))
    ans = 0
    i_sum = A[0]
    for j in range(1, N):
        ans += A[j] * i_sum
        i_sum += A[j]
    print(ans)


if __name__ == "__main__":
    main()
