def main():
    h, w, x, y = map(int, input().split())
    s = []
    for i in range(h):
        s.append(input())
    t = input()

    visited = [[False for _ in range(w)] for _ in range(h)]
    count = 0
    x -= 1
    y -= 1

    for tt in t:
        if tt == "U":
            if x - 1 < 0:
                continue
            if s[x - 1][y] == "#":
                continue
            x -= 1
        elif tt == "D":
            if x + 1 >= h:
                continue
            if s[x + 1][y] == "#":
                continue
            x += 1
        elif tt == "L":
            if y - 1 < 0:
                continue
            if s[x][y - 1] == "#":
                continue
            y -= 1
        elif tt == "R":
            if y + 1 >= w:
                continue
            if s[x][y + 1] == "#":
                continue
            y += 1

        if s[x][y] == ".":
            continue

        if visited[x][y]:
            continue

        count += 1
        visited[x][y] = True

    print(x + 1, y + 1, count)


if __name__ == "__main__":
    main()
