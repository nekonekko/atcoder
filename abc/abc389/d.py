import math


def main():
    R = int(input())

    upper_right = 0
    for i in range(R):
        x = i + 0.5
        h = math.sqrt(R**2 - x**2)
        y = math.floor(h - 0.5)
        upper_right += y
        # print(f"i: {i}, x: {x}, h: {h}, y: {y}, upper_right: {upper_right}")
    print(upper_right * 4 + 1)


if __name__ == "__main__":
    main()
