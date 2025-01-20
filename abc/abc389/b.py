def main():
    x = int(input())
    current, ans = 1, 1
    while ans < x:
        current += 1
        ans *= current
    print(current)


if __name__ == "__main__":
    main()
