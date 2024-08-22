def main():
    n = int(input())
    repunit = [
        1,
        11,
        111,
        1111,
        11111,
        111111,
        1111111,
        11111111,
        111111111,
        1111111111,
        11111111111,
        111111111111,
    ]
    three_rep_sum = set()
    for rep1 in repunit:
        for rep2 in repunit:
            for rep3 in repunit:
                three_rep_sum.add(rep1 + rep2 + rep3)
    sorted_three_rep_sum = sorted(list(three_rep_sum))
    print(sorted_three_rep_sum[n - 1])


if __name__ == "__main__":
    main()
