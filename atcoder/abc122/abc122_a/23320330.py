# region template
import sys
import typing
from typing import Dict, List, Tuple, Union

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    b = sinput().strip()
    if b == "A":
        print("T")
    elif b == "T":
        print("A")
    elif b == "G":
        print("C")
    elif b == "C":
        print("G")
    else:
        raise ValueError


if __name__ == "__main__":
    main()
