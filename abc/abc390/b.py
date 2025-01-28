def main():
    N = int(input())
    A = list(map(int, input().split()))

    for i in range(N - 2):
        if A[i] * A[i + 2] != A[i + 1] ** 2:
            print("No")
            return
    print("Yes")


if __name__ == "__main__":
    main()
