def main():
    N, M = map(int, input().split())
    count = [0] * (N + 1)
    for _ in range(M):
        l, r = map(int, input().split())
        l -= 1  # Convert to 0-based index
        r -= 1
        count[l] += 1
        count[r + 1] -= 1

    for i in range(1, N + 1):
        count[i] += count[i - 1]

    ans = int(1e9)
    for i in range(N):
        ans = min(ans, count[i])
    print(ans)


if __name__ == "__main__":
    main()
