def main():
    N, Q = map(int, input().split())
    X = list(map(int, input().split()))
    num = [0 for _ in range(N + 1)]
    pairs = [[0, i + 1] for i in range(N)]  # [今入っているボールの数、箱の番号]
    for i in range(Q):
        if X[i] >= 1:
            num[X[i]] += 1
            print(f"{X[i]}", end=" ")
            for j in range(N):
                if pairs[j][1] == X[i]:
                    pairs[j][0] += 1
                    break
        else:
            num[pairs[0][1]] += 1
            print(f"{pairs[0][1]}", end=" ")
            pairs[0][0] += 1
        pairs.sort()
        # print(pairs)
    print()


if __name__ == "__main__":
    main()
