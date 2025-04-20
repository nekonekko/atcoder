def main():
    s = input()
    for i in range(len(s)):
        if s[i].isupper():
            print(s[i], end="")
    print()


if __name__ == "__main__":
    main()
