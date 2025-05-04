def main():
    S = input()
    for s in "abcdefghijklmnopqrstuvwxyz":
        if s not in S:
            print(s)
            return


if __name__ == "__main__":
    main()
