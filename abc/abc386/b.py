def main():
    s = input()
    count = 0
    idx = 0
    while True:
        if idx == len(s):
            break

        if s[idx] != "0":
            count += 1
            idx += 1
            continue
        if idx < len(s) - 1 and s[idx + 1] == "0":
            count += 1
            idx += 2
            continue

        count += 1
        idx += 1

    print(count)


if __name__ == "__main__":
    main()
