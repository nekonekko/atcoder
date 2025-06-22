def main():
    N, Q = map(int, input().split())
    A = list(map(int, input().split()))
    is_black = [False] * (N + 2)
    black_count = 0
    for i in range(Q):
        if is_black[A[i]]:
            is_black[A[i]] = False
            # WBW
            if not is_black[A[i] - 1] and not is_black[A[i] + 1]:
                black_count -= 1
            # WBB or BBW
            elif (is_black[A[i] - 1] and not is_black[A[i] + 1]) or (not is_black[A[i] - 1] and is_black[A[i] + 1]):
                black_count += 0
            # BBB
            elif is_black[A[i] - 1] and is_black[A[i] + 1]:
                black_count += 1
        else:
            is_black[A[i]] = True
            # WWW
            if not is_black[A[i] - 1] and not is_black[A[i] + 1]:
                black_count += 1
            # WWB or BWW
            elif (is_black[A[i] - 1] and not is_black[A[i] + 1]) or (not is_black[A[i] - 1] and is_black[A[i] + 1]):
                black_count += 0
            # BWB
            elif is_black[A[i] - 1] and is_black[A[i] + 1]:
                black_count -= 1
        print(black_count)

if __name__ == "__main__":
    main()
