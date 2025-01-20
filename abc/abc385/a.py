def main():
    a, b, c = map(int, input().split())
    a, b, c = sorted([a, b, c])
    if a + b == c or (a == b and b == c):
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
