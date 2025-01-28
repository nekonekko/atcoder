from collections import defaultdict


def main():
    a, b, c, d, e = map(int, input().split())
    dic = defaultdict(list)
    for e_i in [1, 0]:
        for d_i in [1, 0]:
            for c_i in [1, 0]:
                for b_i in [1, 0]:
                    for a_i in [1, 0]:
                        s = ""
                        if a_i == 1:
                            s += "A"
                        if b_i == 1:
                            s += "B"
                        if c_i == 1:
                            s += "C"
                        if d_i == 1:
                            s += "D"
                        if e_i == 1:
                            s += "E"
                        dic[a_i * a + b_i * b + c_i * c + d_i * d + e_i * e].append(s)

    keys = sorted(dic.keys(), reverse=True)
    for key in keys:
        values = dic[key]
        for value in sorted(values):
            print(value)


if __name__ == "__main__":
    main()
