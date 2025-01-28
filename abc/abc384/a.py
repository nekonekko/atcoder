def main():
    N, c1, c2 = input().split()
    N = int(N)
    S = input()
    for s in S:
        if s != c1:
            print(c2, end="")
        else:
            print(s, end="")
    print()


if __name__ == "__main__":
    main()
