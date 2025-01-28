def main():
    N, R = map(int, input().split())
    for i in range(N):
        D, A = map(int, input().split())
        if D == 1:
            if 1600 <= R and R <= 2799:
                R += A
        else:
            if 1200 <= R and R <= 2399:
                R += A
    print(R)


if __name__ == "__main__":
    main()
