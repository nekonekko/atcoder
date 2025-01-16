def insert(i, s, t):
    if len(s) + 1 != len(t):
        return False

    for j in range(i, len(s)):
        if s[j] != t[j + 1]:
            return False

    # print("can insert")

    return True


def delete(i, s, t):
    if len(s) - 1 != len(t):
        return False

    for j in range(i + 1, len(s)):
        if s[j] != t[j - 1]:
            return False

    # print("can delete")

    return True


def replace(i, s, t):
    if len(s) != len(t):
        return False

    for j in range(i + 1, len(s)):
        if s[j] != t[j]:
            return False

    # print("can replace")

    return True


def main():
    k = int(input())
    s = input()
    t = input()

    if abs(len(s) - len(t)) > k:
        print("No")
        return

    if s == t:
        print("Yes")
        return

    if len(s) < len(t):
        for i in range(len(s)):
            if s[i] != t[i]:
                if insert(i, s, t):
                    print("Yes")
                    return
                print("No")
                return

        print("Yes")
        return

    if len(s) > len(t):
        for i in range(len(t)):
            if s[i] != t[i]:
                if delete(i, s, t):
                    print("Yes")
                    return
                print("No")
                return

        print("Yes")
        return

    if len(s) == len(t):
        for i in range(len(s)):
            if s[i] != t[i]:
                if replace(i, s, t):
                    print("Yes")
                    return
                print("No")
                return


if __name__ == "__main__":
    main()
