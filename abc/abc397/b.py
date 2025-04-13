def main():
    S = input()
    ans = 0
    idx = 0
    i = 0
    while idx < len(S):
        if i % 2 == 1:
            if S[idx] == "i":
                ans += 1
                i += 1
                continue
            idx += 1
            i += 1
            continue
        if S[idx] == "i":
            idx += 1
            i += 1
            continue
        ans += 1
        i += 1
    if S[-1] == "i":
        ans += 1
    print(ans)


if __name__ == "__main__":
    main()
