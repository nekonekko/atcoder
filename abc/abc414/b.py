def main():
    N = int(input())
    C_list = []
    L_list = []

    for i in range(N):
        C, L = input().split()
        L = int(L)
        C_list.append(C)
        L_list.append(L)

    ans = ""
    length = 0
    idx = 0
    while idx < N and length <= 100:
        if length + L_list[idx] <= 100:
            ans += C_list[idx] * L_list[idx]
            length += L_list[idx]
        else:
            break
        idx += 1
    if idx == N:
        print(ans)
        return
    print("Too Long")


if __name__ == "__main__":
    main()
