def main():
    N, Q = map(int, input().split())
    A = [i + 1 for i in range(N)]
    head_idx = 0
    for _ in range(Q):
        query = list(map(int, input().split()))
        query_type = query[0]
        if query_type == 1:
            p, x = query[1], query[2]
            A[(head_idx + p - 1) % N] = x
        elif query_type == 2:
            p = query[1]
            print(A[(head_idx + p - 1) % N])
        elif query_type == 3:
            k = query[1]
            head_idx = (head_idx + k) % N


if __name__ == "__main__":
    main()
