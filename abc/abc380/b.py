def main():
    S = input()
    a = S.split("|")
    for i in range(1, len(a) - 1):
        print(len(a[i]), end=" ")
    print()


if __name__ == "__main__":
    main()
