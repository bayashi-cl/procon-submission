# region template
import sys
import typing
from string import ascii_uppercase

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
    s = sinput().strip()
    num = []
    for si in s:
        num.append((ord(si) - ord("A") + n) % 26)
    ans = [ascii_uppercase[i] for i in num]
    print("".join(ans))


if __name__ == "__main__":
    main()
