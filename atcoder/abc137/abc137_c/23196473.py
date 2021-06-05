# region template
import sys
import typing
from collections import Counter

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    cn = []
    for i in range(n):
        s = sinput().strip()
        char = [0] * 26
        for si in s:
            char[ord(si) - 97] += 1
        cn.append(tuple(char))

    cnt = Counter(cn)

    ans = 0
    for v in cnt.values():
        ans += v * (v - 1) // 2
    print(ans)


if __name__ == "__main__":
    main()
