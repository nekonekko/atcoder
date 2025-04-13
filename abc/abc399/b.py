def main():
    N = int(input())
    P = list(map(int, input().split()))
    cnt = dict()
    for i in range(N):
        cnt[P[i]] = cnt.get(P[i], 0) + 1
    val = sorted(cnt.keys(), reverse=True)
    rank = 1
    val_to_rank = dict()
    for v in val:
        val_to_rank[v] = rank
        rank += cnt[v]
    for i in range(N):
        print(val_to_rank[P[i]])


if __name__ == "__main__":
    main()
