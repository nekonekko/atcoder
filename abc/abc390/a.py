def main():
    a, b, c, d, e = map(int, input().split())
    s = f"{a}{b}{c}{d}{e}"
    if s in ["21345", "13245", "12435", "12354"]:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
