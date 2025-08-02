import math

def main():
    N = int(input())
    
    MOD = 998244353

    ans = (N * (N + 1) // 2) % MOD
    
    k = 1
    while k * k <= N:
        left = N // (k + 1) + 1
        right = N // k
        if left <= right:
            ans -= (right - left + 1) * k % MOD
            ans %= MOD
        k += 1
    
    for b in range(1, N // k + 1):
        ans -= (N // b) % MOD
        ans %= MOD

    
    print(ans)

if __name__ == '__main__':
    main()
