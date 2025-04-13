def main():
    N = int(input())
    A = list(map(int, input().split()))
    for i in range(len(A) - 1):
        if A[i] >= A[i + 1]:
            print("No")
            return
    print("Yes")


if __name__ == "__main__":
    main()
