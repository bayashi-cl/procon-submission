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


def prime_factorize(n: int) -> typing.List[int]:
    a = []
    while n % 2 == 0:
        a.append(2)
        n //= 2
    f = 3
    while f * f <= n:
        if n % f == 0:
            a.append(f)
            n //= f
        else:
            f += 2
    if n != 1:
        a.append(n)
    return a


def meguru_search(
    ok: int, ng: int, is_ok: typing.Callable[[int, typing.Any], bool], *args
) -> int:
    assert is_ok(ok, *args)
    assert not is_ok(ng, *args)

    while abs(ok - ng) > 1:
        mid = (ok + ng) // 2
        if is_ok(mid, *args):
            ok = mid
        else:
            ng = mid
    return ok


def main() -> None:
    n = int(sinput())
    primes = Counter(prime_factorize(n))

    def is_ok(mid: int, k: int) -> bool:
        return mid * (mid + 1) // 2 <= k

    ans = 0
    for v in primes.values():
        ans += meguru_search(0, v + 1, is_ok, v)

    print(ans)


if __name__ == "__main__":
    main()
