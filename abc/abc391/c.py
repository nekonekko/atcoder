def main():
    N, Q = map(int, input().split())
    multiple_hato_su = set()
    hato_count = [1 for _ in range(N)]
    hato_place = [i for i in range(N)]
    for _ in range(Q):
        query = input()
        if query[0] == "1":
            _, p, h = map(int, query.split())
            p -= 1
            h -= 1
            # 元いた場所から移動させる
            # 移動まえの処理
            hato_count[hato_place[p]] -= 1
            if hato_count[hato_place[p]] <= 1 and hato_place[p] in multiple_hato_su:
                multiple_hato_su.remove(hato_place[p])
            # 移動後の処理
            hato_place[p] = h
            hato_count[hato_place[p]] += 1
            if hato_count[hato_place[p]] >= 2:
                multiple_hato_su.add(hato_place[p])
        else:
            print(len(multiple_hato_su))


if __name__ == "__main__":
    main()
