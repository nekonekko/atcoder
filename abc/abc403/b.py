def main():
    T = input()
    U = input()
    exist = False
    for i in range(len(T)):
        if i + len(U) > len(T):
            break
        ok = True
        for j in range(len(U)):
            if T[i + j] != "?" and T[i + j] != U[j]:
                ok = False
                break
        if ok:
            exist = True
            break
    if exist:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
