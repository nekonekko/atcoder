def main():
    N = int(input())
    a, b = 1, 1
    while a <= N:
        b = 1
        while a * b <= N:
            if a * b == N:
                print("Yes")
                return
            b *= 3
        a *= 2

    print("No")


if __name__ == "__main__":
    main()
