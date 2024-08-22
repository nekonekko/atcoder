def main():
    s = input()
    t = input()
    alphabetToNumber = {"A": 0, "B": 1, "C": 2, "D": 3, "E": 4}
    s1, s2 = alphabetToNumber[s[0]], alphabetToNumber[s[1]]
    t1, t2 = alphabetToNumber[t[0]], alphabetToNumber[t[1]]
    s_dist = min(abs(s1 - s2), 5 - abs(s1 - s2))
    t_dist = min(abs(t1 - t2), 5 - abs(t1 - t2))
    if s_dist == t_dist:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
