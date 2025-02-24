def main():
    N, M = map(int, input().split())
    edges = set()
    ans = 0
    for _ in range(M):
        a, b = map(int, input().split())
        if a == b:
            ans += 1
            continue
        if a > b:
            a, b = b, a
        if (a, b) in edges:
            ans += 1
        else:
            edges.add((a, b))
    print(ans)


if __name__ == "__main__":
    main()
