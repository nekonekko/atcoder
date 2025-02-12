def main():
    N, M = map(int, input().split())
    A = list(map(int, input().split()))
    X = []
    for i in range(1, N + 1):
        if i not in A:
            X.append(i)
    print(len(X))
    if len(X) == 0:
        print("")
        return
    for x in X:
        print(x, end=" ")
    print("")


if __name__ == "__main__":
    main()
