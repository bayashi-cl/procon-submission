# region template
import sys
import typing
from decimal import Decimal
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def main() -> None:
    x = Decimal(sinput().strip())
    print(x.quantize(Decimal("1."), rounding="ROUND_HALF_UP"))
    # x = sinput().strip()
    # a, b = x.split(".")
    # ai = int(a)
    # if int(b[0]) >= 5:
    #     ai += 1
    # print(ai)


if __name__ == "__main__":
    main()
