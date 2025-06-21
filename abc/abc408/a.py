def main():
    N, S = map(int, input().split())
    T = list(map(int, input().split()))
    T = [0] + T
    for i in range(N):
        if T[i + 1] - T[i] > S:
            print("No")
            return
    print("Yes")


if __name__ == "__main__":
    main()
