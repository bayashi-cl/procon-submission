# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import defaultdict

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


# def main() -> None:
#     n = int(sinput())
#     s = set()
#     zero = defaultdict(list)
#     for _ in range(n):
#         si = sinput().strip()
#         k = int(si)
#         n_zero = 0
#         for i, d in enumerate(si):
#             if d != "0":
#                 n_zero = i
#                 break
#         else:
#             n_zero = len(si)

#         zero[k].append(n_zero)
#         s.add(k)

#     ks = list(s)
#     ks.sort()
#     for k in ks:
#         zl = zero[k]
#         zl.sort()
#         for nz in zl:
#             print()
#         # for


def sep(s: str):
    for i, d in enumerate(s):
        if d != "0":
            return (int(s), MOD - i)
    return (0, MOD - len(s) + 1)


def main() -> None:
    n = int(sinput())
    s = list()
    for _ in range(n):
        si = sinput().strip()
        s.append(sep(si))
    s.sort()
    for k, z in s:
        print("0" * (MOD - z) + str(k))


if __name__ == "__main__":
    main()
