def main():
    a, b, c, d = map(int, input().split())
    a, b, c, d = sorted([a, b, c, d])
    if a == b and b == c and c == d:
        print("No")
        return

    if (a == b and b == c) or (b == c and c == d):
        print("Yes")
        return

    if a == b and c == d:
        print("Yes")
        return

    print("No")


if __name__ == "__main__":
    main()
