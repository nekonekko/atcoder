def main():
    q = int(input())
    queue = []
    idx = 0
    for i in range(q):
        query = input()
        if query[0] == "1":
            _, x = query.split()
            queue.append(int(x))
        else:
            print(queue[idx])
            idx += 1


if __name__ == "__main__":
    main()
