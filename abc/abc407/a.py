import math


def main():
    A, B = map(int, input().split())
    ceil = math.ceil(A / B) - A / B
    floor = A / B - math.floor(A / B)
    if ceil < floor:
        print(math.ceil(A / B))
    else:
        print(math.floor(A / B))


if __name__ == "__main__":
    main()
