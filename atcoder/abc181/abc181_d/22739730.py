def main() -> None:
    # region template
    import sys
    import typing

    sys.setrecursionlimit(10 ** 6)
    Vec = typing.List[int]  # noqa:F841
    VecVec = typing.List[Vec]  # noqa:F841
    sinput: typing.Callable[..., str] = sys.stdin.readline  # noqa:F841
    MOD: int = 1000000007  # noqa:F841
    INF: float = float("Inf")  # noqa:F841
    IINF: int = 4611686018427387903  # noqa:F841
    # endregion

    from collections import defaultdict
    from itertools import permutations

    S = sinput().strip()

    if len(S) <= 3:
        for p in permutations(S):
            if int("".join(p)) % 8 == 0:
                print("Yes")
                break
        else:
            print("No")
        return

    s_dic = defaultdict(int)

    for s in S:
        s_dic[s] += 1

    for i in range(0, 1000, 8):
        i_dic = defaultdict(int)
        for si in str(i).zfill(3):
            i_dic[si] += 1

        flag = True
        for k, v in i_dic.items():
            if s_dic[k] < v:
                flag = False

        if flag:
            print("Yes")
            break
    else:
        print("No")


if __name__ == "__main__":
    main()
