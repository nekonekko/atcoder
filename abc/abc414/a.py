def main():
    N, L, R = map(int, input().split())
    ans = 0
    for i in range(N):
        X, Y  = map(int, input().split())
        if X <= L and R <= Y:
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
