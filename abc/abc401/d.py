def main():
    N, K = map(int, input().split())
    S = input()

    # oの両隣の?を.に置き換える
    S = S.replace("?o", ".o")
    S = S.replace("o?", "o.")

    # その?の集合が何番目の集合かと、集合の大きさを調べる
    order_list = [-1 for _ in range(N)]
    order = 0
    size = []
    i = 0
    while i < N:
        if S[i] == "?":
            j = i
            while j < N and S[j] == "?":
                order_list[j] = order
                j += 1
            size.append(j - i)
            order += 1
            i = j
        else:
            i += 1

    # debug
    # print(order_list)
    # print(size)

    # oの数を数える
    o_count = S.count("o")
    # 新しく作れるoの数を数える
    new_o_count = 0
    for sz in size:
        if sz % 2 == 0:
            new_o_count += sz // 2
        else:
            new_o_count += (sz + 1) // 2

    # Kちょうどのとき
    # 偶数個の?の集合は?のまま
    # 奇数個の?の集合はo.o.o. .... .o になる
    if o_count + new_o_count == K:
        i = 0
        while i < N:
            if S[i] == "?":
                if size[order_list[i]] % 2 == 0:
                    for j in range(size[order_list[i]]):
                        print("?", end="")
                    i += size[order_list[i]]
                    continue
                for j in range(size[order_list[i]]):
                    if j % 2 == 0:
                        print("o", end="")
                    else:
                        print(".", end="")
                i += size[order_list[i]]
            else:
                print(S[i], end="")
                i += 1
        print()
        return 0

    if o_count == K:
        S = S.replace("?", ".")
        print(S)
        return 0

    print(S)


if __name__ == "__main__":
    main()
