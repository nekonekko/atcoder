def main():
    N = int(input())
    ans = [["_" for _ in range(N)] for _ in range(N)]
    for i in range(N):
        j = N - i - 1
        if i <= j:
            if i % 2 == 0:
                color = "#"
            else:
                color = "."
            for ii in range(i, j + 1):
                for jj in range(i, j + 1):
                    ans[ii][jj] = color
    for i in range(N):
        print("".join(ans[i]))


if __name__ == "__main__":
    main()
