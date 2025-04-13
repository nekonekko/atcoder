def main():
    N = int(input())
    A = list(map(int, input().split()))
    mp = dict()
    for i, a in enumerate(A):
        if mp.get(a):
            mp[a].append(i)
        else:
            mp[a] = [i]
    ans = 2 * N
    for k, v in mp.items():
        if len(v) == 1:
            continue
        v.sort()
        for i in range(len(v) - 1):
            diff = v[i + 1] - v[i] + 1
            ans = min(ans, diff)

    if ans == 2 * N:
        print(-1)
    else:
        print(ans)


if __name__ == "__main__":
    main()
