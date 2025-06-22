def main():
    N = int(input())
    P = list(map(int, input().split()))
    signs = []
    for i in range(1, N):
        if P[i] > P[i - 1]:
            signs.append(1)
        else:
            signs.append(-1)

    count = 1
    counts = []
    for i in range(1, len(signs)):
        if signs[i] == signs[i - 1]:
            count += 1
        else:
            if signs[i - 1] == 1:
                counts.append(count)
            count = 1
    if signs[-1] == 1:
        counts.append(count)
        
    # print(signs)
    # print(counts)

    ans = 0
    for i in range(1, len(counts)):
        ans += counts[i - 1] * counts[i]
        
    print(ans)

if __name__ == "__main__":
    main()
