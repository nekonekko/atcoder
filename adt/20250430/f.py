from collections import defaultdict


def main():
    N = int(input())
    mp = defaultdict(list)
    for i in range(N):
        F, S = map(int, input().split())
        mp[F].append(S)

    same_flavor_max = 0
    max_flavors = []
    for k in mp.keys():
        mp[k].sort(reverse=True)
        max_flavors.append(mp[k][0])
        if len(mp[k]) >= 2:
            same_flavor_max = max(same_flavor_max, mp[k][0] + int(mp[k][1] / 2))

    max_flavors.sort(reverse=True)
    if len(max_flavors) >= 2:
        ans = max(max_flavors[0] + max_flavors[1], same_flavor_max)
    else:
        ans = same_flavor_max

    print(ans)


if __name__ == "__main__":
    main()
