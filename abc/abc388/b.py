def main():
    n, d = map(int, input().split())
    t_list, l_list = [], []
    for i in range(n):
        t, l = map(int, input().split())
        t_list.append(t)
        l_list.append(l)

    for k in range(1, d + 1):
        ans = 0
        for i in range(n):
            ans = max(ans, t_list[i] * (l_list[i] + k))
        print(ans)


if __name__ == "__main__":
    main()
