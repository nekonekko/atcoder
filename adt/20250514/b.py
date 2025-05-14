def main():
    x = int(input())
    ans = 0
    if x <= 10:
        ans = 10
    elif x <= 15:
        ans = 15
    else:
        ans = 17
    print(ans)


if __name__ == "__main__":
    main()
