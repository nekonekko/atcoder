def main():
    n = int(input())
    logged_in = False
    ans = 0
    for i in range(n):
        s = input()
        if s == "login":
            logged_in = True
        elif s == "logout":
            logged_in = False
        elif s == "private" and not logged_in:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
