def main():
    n = int(input())
    h = list(map(int, input().split()))

    ans = 1
    for i in range(n):
        for span in range(1, n):
            if i + span > n:
                break
            cnt = 1
            j = i
            while j + span < n and h[j + span] == h[i]:
                cnt += 1
                j += span
            ans = max(ans, cnt)
    print(ans)


if __name__ == "__main__":
    main()
