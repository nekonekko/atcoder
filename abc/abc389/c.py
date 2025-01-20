def main():
    Q = int(input())
    queue = [0 for _ in range(Q + 1)]
    num_snake_sum = 0
    num_escape = 0
    for _ in range(Q):
        s = input()
        if s[0] == "1":
            l = int(s.split()[1])
            queue[num_snake_sum + 1] = queue[num_snake_sum] + l
            num_snake_sum += 1
            # print(queue)
        elif s[0] == "2":
            num_escape += 1
        else:
            k = int(s.split()[1])
            print(queue[num_escape + k - 1] - queue[num_escape])


if __name__ == "__main__":
    main()
