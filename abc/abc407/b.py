def main():
    X, Y = map(int, input().split())
    cnt = 0
    for i in range(1, 7):
        for j in range(1, 7):
            if i + j >= X or abs(i - j) >= Y:
                cnt += 1

    print(cnt / 36)


if __name__ == "__main__":
    main()
