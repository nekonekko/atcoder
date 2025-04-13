def main():
    N = int(input())
    A = list(map(int, input().split()))

    fst_dict = dict()
    fst_set = set()
    snd_dict = dict()
    snd_set = set()

    fst_dict[A[0]] = 1
    fst_set.add(A[0])

    for i in range(1, N):
        if snd_dict.get(A[i]) is None:
            snd_dict[A[i]] = 1
            snd_set.add(A[i])
        else:
            snd_dict[A[i]] += 1

    ans = len(fst_set) + len(snd_set)
    for i in range(1, N - 1):
        # print(fst_set, snd_set)
        snd_dict[A[i]] -= 1

        if snd_dict[A[i]] == 0:
            snd_set.remove(A[i])

        if fst_dict.get(A[i]) is None:
            fst_dict[A[i]] = 1
            fst_set.add(A[i])
        else:
            fst_dict[A[i]] += 1

        ans = max(ans, len(fst_set) + len(snd_set))

    print(ans)


if __name__ == "__main__":
    main()
