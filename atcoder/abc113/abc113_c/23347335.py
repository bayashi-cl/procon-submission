# region template
import sys
import typing
from collections import defaultdict
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
    n, m = map(int, sinput().split())
    # city = [tuple(map(int, sinput().split())) for _ in range(m)]
    city = []
    for i in range(m):
        p, y = map(int, sinput().split())
        city.append((p, y, i))
    city.sort(key=itemgetter(1))

    prefecture = defaultdict(int)
    city_code = [""] * m
    for p, y, i in city:
        prefecture[p] += 1
        code = str(p).zfill(6) + str(prefecture[p]).zfill(6)
        city_code[i] = code

    print("\n".join(city_code))


if __name__ == "__main__":
    main()
