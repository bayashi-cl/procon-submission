# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import deque
from itertools import accumulate

# from operator import add

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    q = int(sinput())
    que: typing.Deque[int] = deque()
    # one_cs = [0] * q
    # three: List[Tuple[int, int]] = []

    for i in range(q):
        t, x = map(int, sinput().split())

        if t == 1:
            que.appendleft(x)
            # one_cs[i] = 1
        elif t == 2:
            que.append(x)
        elif t == 3:
            # three.append((i, x - 1))
            print(que[x - 1])
        else:
            raise ValueError

    # one_cs = list(accumulate(one_cs, initial=0))
    # deck = list(que)
    # for i, x in three:
    #     ex = one_cs[-1] - one_cs[i]
    #     print(deck[x + ex])


if __name__ == "__main__":
    main()
