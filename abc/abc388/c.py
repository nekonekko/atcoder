def main():
    n = int(input())
    a_str = input()
    mochi_size = list(map(int, a_str.split()))

    ans = 0
    oya_idx = 0
    for i in range(n):
        while oya_idx < n and mochi_size[oya_idx] < 2 * mochi_size[i]:
            oya_idx += 1
        if oya_idx == n:
            break
        ans += n - oya_idx

    print(ans)


if __name__ == "__main__":
    main()
