class Elem:
    def __init__(self, x, y, cnt, before_direction):
        self.x = x
        self.y = y
        self.cnt = cnt
        self.before_direction = before_direction  # 0: 縦, 1: 横


def can_move(x, y, H, W, grid):
    if x < 0 or x >= H or y < 0 or y >= W:
        return False
    if grid[x][y] == "#":
        return False
    return True


def main():
    H, W = map(int, input().split())
    grid = [list(input()) for _ in range(H)]

    for i in range(H):
        for j in range(W):
            if grid[i][j] == "S":
                start = (i, j)
            elif grid[i][j] == "G":
                goal = (i, j)

    dx_list = [1, 0, -1, 0]  # x が H 方向
    dy_list = [0, 1, 0, -1]  # y が W 方向
    dist_vertical = [[-1] * W for _ in range(H)]
    dist_horizontal = [[-1] * W for _ in range(H)]

    queue = [Elem(start[0], start[1], 0, 0), Elem(start[0], start[1], 0, 1)]

    while queue:
        elem = queue.pop(0)
        if elem.before_direction == 0:
            # 前の移動が縦の場合
            if dist_vertical[elem.x][elem.y] != -1:
                continue
            dist_vertical[elem.x][elem.y] = elem.cnt
        else:
            # 前の移動が横の場合
            if dist_horizontal[elem.x][elem.y] != -1:
                continue
            dist_horizontal[elem.x][elem.y] = elem.cnt

        for i, (dx, dy) in enumerate(zip(dx_list, dy_list)):
            if elem.before_direction == (i % 2):
                # 前と同じ方向の移動はスキップ
                continue
            next_pos = (elem.x + dx, elem.y + dy)
            if not can_move(next_pos[0], next_pos[1], H, W, grid):
                continue
            if next_pos == goal:
                print(elem.cnt + 1)
                return
            queue.append(Elem(next_pos[0], next_pos[1], elem.cnt + 1, i % 2))

    print(-1)


if __name__ == "__main__":
    main()
