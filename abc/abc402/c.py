def main():
    N, M = map(int, input().split())
    remain_nigate = []
    ingre_dish = [[] for _ in range(N)]
    for i in range(M):
        q = list(map(int, input().split()))
        k = q[0]
        a = q[1:]
        remain_nigate.append(k)
        for aa in a:
            ingre_dish[aa - 1].append(i)

    can_eat = 0
    b = list(map(int, input().split()))
    for bb in b:
        for dish in ingre_dish[bb - 1]:
            remain_nigate[dish] -= 1
            if remain_nigate[dish] == 0:
                can_eat += 1
        print(can_eat)


if __name__ == "__main__":
    main()
