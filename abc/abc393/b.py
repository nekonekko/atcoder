def main():
    s = input()
    ans = 0
    for i in range(len(s)):
        for j in range(i + 1, len(s)):
            for k in range(j + 1, len(s)):
                if k - j != j - i:
                    continue
                if s[i] == "A" and s[j] == "B" and s[k] == "C":
                    ans += 1
    print(ans)


if __name__ == "__main__":
    main()
