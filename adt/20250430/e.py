import bisect


def main():
    N, M = map(int, input().split())
    A = list(map(int, input().split()))
    for i in range(1, N + 1):
        idx = bisect.bisect_left(A, i)
        print(A[idx] - i)


if __name__ == "__main__":
    main()
