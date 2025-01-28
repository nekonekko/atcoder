def main():
    H, W = map(int, input().split())
    S = [input() for _ in range(H)]

    most_left, most_right, most_top, most_bottom = 1000000, -1, 100000, -1
    for i in range(H):
        for j in range(W):
            if S[i][j] == "#":
                most_left = min(most_left, j)
                most_right = max(most_right, j)
                most_top = min(most_top, i)
                most_bottom = max(most_bottom, i)

    for i in range(H):
        for j in range(W):
            if (
                most_left <= j
                and j <= most_right
                and most_top <= i
                and i <= most_bottom
            ):
                if S[i][j] == ".":
                    print("No")
                    return

    print("Yes")


if __name__ == "__main__":
    main()
