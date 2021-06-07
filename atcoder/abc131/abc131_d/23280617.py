# region template
import sys
import typing
from operator import itemgetter

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
    task = [tuple(map(int, sinput().split())) for _ in range(n)]
    task.sort(key=itemgetter(1))

    now = 0
    for a, b in task:
        now += a
        if now > b:
            break
    else:
        print("Yes")
        return
    print("No")


if __name__ == "__main__":
    main()
