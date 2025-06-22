def main():
    A, B, C, D = map(int, input().split())
    if C < A:
        print("Yes")
        return
    if C > A:
        print("No")
        return
    if D <= B:
        print("Yes")
        return
    print("No")


if __name__ == "__main__":
    main()
