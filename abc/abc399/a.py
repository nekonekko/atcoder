def main():
    N = int(input())
    S = input()
    T = input()
    ans = 0
    for i in range(N):
        if S[i] != T[i]:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
