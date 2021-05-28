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
    a = Counter(map(lambda x: int(x) % 46, sinput().split()))
    b = Counter(map(lambda x: int(x) % 46, sinput().split()))
    c = Counter(map(lambda x: int(x) % 46, sinput().split()))

    ans = 0

    for i in range(47):
        for j in range(47):
            for k in range(47):
                if (i + j + k) % 46 == 0:
                    ans += a[i] * b[j] * c[k]

    print(ans)


if __name__ == "__main__":
    main()
