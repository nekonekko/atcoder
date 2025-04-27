def main():
    N, K = map(int, input().split())
    S = input()
    k_1_end = 0
    k_start = 0
    k_end = 0
    idx = 0
    n_k = 0
    while idx < N:
        start = idx
        if S[idx] == "0":
            while idx < N and S[idx] == "0":
                idx += 1
        else:
            while idx < N and S[idx] == "1":
                idx += 1
            n_k += 1
            if n_k == K - 1:
                k_1_end = idx
            if n_k == K:
                k_start = start
                k_end = idx

    ans = S[:k_1_end] + S[k_start:k_end] + S[k_1_end:k_start] + S[k_end:]
    print(ans)


if __name__ == "__main__":
    main()
