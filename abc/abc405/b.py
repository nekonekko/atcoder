def main():
    N, M = map(int, input().split())
    A = list(map(int, input().split()))
    initial_idx = [-1 for _ in range(M)]
    for i in range(N):
        if initial_idx[A[i] - 1] == -1:
            initial_idx[A[i] - 1] = i
    for i in range(M):
        if initial_idx[i] == -1:
            print(0)
            return
    max_initial_idx = max(initial_idx)
    print(N - max_initial_idx)


if __name__ == "__main__":
    main()
