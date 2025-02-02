def main():
    N, M = map(int, input().split())
    S = [list(input()) for _ in range(N)]
    T = [list(input()) for _ in range(M)]

    for i in range(N - M + 1):
        for j in range(N - M + 1):
            for k in range(M):
                if S[i + k][j : j + M] != T[k]:
                    break
            else:
                print(i + 1, j + 1)
                return


if __name__ == "__main__":
    main()
