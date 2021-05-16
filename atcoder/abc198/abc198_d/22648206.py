# region template
import sys
import typing
from itertools import permutations

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def assemble(word, n):
    res = 0
    for s in word:
        res *= 10
        res += n[s]
    return res


def main() -> None:
    s1 = list(sinput().strip())
    s2 = list(sinput().strip())
    s3 = list(sinput().strip())

    letter = list(set(s1 + s2 + s3))
    s1_num = []
    for s in s1:
        s1_num.append(letter.index(s))
    s2_num = []
    for s in s2:
        s2_num.append(letter.index(s))
    s3_num = []
    for s in s3:
        s3_num.append(letter.index(s))

    head = (letter.index(s1[0]), letter.index(s2[0]), letter.index(s3[0]))
    kind = len(letter)
    if kind > 10:
        print("UNSOLVABLE")
        return

    for p in permutations(range(10), kind):
        flag = False
        for h in head:
            if p[h] == 0:
                flag = True
        if flag:
            continue
        s1_int = assemble(s1_num, p)
        s2_int = assemble(s2_num, p)
        s3_int = assemble(s3_num, p)

        if s1_int + s2_int == s3_int:
            print(s1_int)
            print(s2_int)
            print(s3_int)
            break
    else:
        print("UNSOLVABLE")


if __name__ == "__main__":
    main()
