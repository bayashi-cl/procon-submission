# region template
import sys
import typing

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    s = int(sinput())
    se = {s}
    m = 2
    while True:
        if s % 2 == 0:
            s = s // 2
        else:
            s = 3 * s + 1
        if s in se:
            break
        else:
            se.add(s)
        m += 1

    print(m)


if __name__ == "__main__":
    main()
