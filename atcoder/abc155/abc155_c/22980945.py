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
    _ = int(sinput())
    s = Counter(si.strip() for si in sys.stdin.readlines())
    ans = []
    _, max_num = s.most_common()[0]
    for poll, num in s.most_common():
        if num == max_num:
            ans.append(poll)
        else:
            break
    ans.sort()
    print("\n".join(ans))


if __name__ == "__main__":
    main()
