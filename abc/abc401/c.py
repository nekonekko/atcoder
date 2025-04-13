def main():
    N, K = map(int, input().split())
    MOD = int(10**9)
    # if K > N:
    #     print(1)
    #     return
    A = [0]
    for i in range(1, K):
        A.append(A[i - 1] + 1)
        A[i] %= MOD
    A.append(A[K - 1] + K)
    A[K] %= MOD
    for i in range(K + 1, N + 1):
        A_i = A[i - 1] - A[i - K - 1]
        A.append(A[i - 1] + A_i)
        A[i] %= MOD
    print(A[N] - A[N - 1] + MOD if A[N] - A[N - 1] < 0 else A[N] - A[N - 1])


if __name__ == "__main__":
    main()
