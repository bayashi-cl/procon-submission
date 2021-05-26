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
    s = sinput().strip()

    mod = [0] * len(s)
    temp = 0
    for i in range(len(s)):
        si = int(s[-i - 1])
        temp += si * pow(10, i, 2019)
        temp %= 2019
        mod[-i - 1] = temp

    print(mod, file=sys.stderr)
    cnt = Counter(mod)
    ans = 0
    for v in cnt.values():
        ans += (v - 1) * v // 2

    print(ans + cnt[0])


if __name__ == "__main__":
    main()
