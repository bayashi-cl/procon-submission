# region template
import sys
import typing

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def mono_comb(n: int, r: int, mod: int = 10 ** 9 + 7) -> int:
    """二項係数
    **O(r)**
    python3.8 or later
    """
    r = min(r, n - r)
    numer = 1
    denom = 1
    for i in range(r):
        numer *= n - i
        denom *= r - i

        numer %= mod
        denom %= mod

    denom_mod = pow(denom, -1, mod)
    return (numer * denom_mod) % mod


def main() -> None:
    x, y = map(int, sinput().split())
    if (x + y) % 3 != 0:
        print(0)
        return
    turn = (x + y) // 3

    if y < turn or y > 2 * turn:
        print(0)
        return
    v = y - turn

    ans = mono_comb(turn, v)
    print(ans)


if __name__ == "__main__":
    main()
