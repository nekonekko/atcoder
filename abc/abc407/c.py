def main():
    S = input()
    cnt = int(S[-1])
    for i in range(len(S) - 2, -1, -1):
        pls = 0
        while (cnt + pls) % 10 != int(S[i]):
            pls += 1
        cnt += pls
    cnt += len(S)
    print(cnt)


if __name__ == "__main__":
    main()
