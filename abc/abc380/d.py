import math


def calc_jousu(n_S):
    nn = 1
    while nn * 2 < n_S:
        nn *= 2
    return nn


def main():
    S = input()
    Q = int(input())
    K = list(map(int, input().split()))
    N = len(S)
    for k in K:
        s = S[(k - 1) % N]
        n_words = (k + N - 1) // N - 1
        cnt = 0
        while n_words > 0:
            cnt += n_words & 1
            n_words >>= 1
        # print(cnt, n_words, end=" ")
        if cnt % 2 == 0:
            print(s, end=" ")
        else:
            if s.isupper():
                print(s.lower(), end=" ")
            else:
                print(s.upper(), end=" ")
        # print()
    print()


if __name__ == "__main__":
    main()
