def main():
    N, M = map(int, input().split())
    chuten_dict = dict()
    for i in range(M):
        a, b = map(int, input().split())
        chuten = a + b
        if chuten > N:
            chuten -= N
        if chuten not in chuten_dict:
            chuten_dict[chuten] = 1
        else:
            chuten_dict[chuten] += 1
    heikou = 0
    for val in chuten_dict.values():
        heikou += int(val * (val - 1) // 2)
    print(M * (M - 1) // 2 - heikou)


if __name__ == "__main__":
    main()
