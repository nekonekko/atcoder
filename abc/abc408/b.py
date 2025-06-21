def main():
    N = int(input())
    A = list(map(int, input().split()))

    S = list(set(A))
    S.sort()
    print(len(S))
    print(" ".join(map(str, S)))


if __name__ == "__main__":
    main()
