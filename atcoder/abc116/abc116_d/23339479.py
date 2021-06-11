# region template
import sys
import typing
from collections import defaultdict, Counter
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
    n, k = map(int, sinput().split())
    sushi = [tuple(map(int, sinput().split())) for _ in range(n)]

    sushi.sort(key=itemgetter(1), reverse=True)

    kind = Counter()
    score = 0
    for t, d in sushi[:k]:
        kind[t] += 1
        score += d
    r = k - 1
    lk = len(kind)
    ans = score + lk ** 2

    for t, d in sushi[k:]:
        if t in kind:
            continue

        while r >= 0:
            r_t, r_d = sushi[r]
            if kind[r_t] >= 2:
                break
            else:
                r -= 1
        else:
            break

        score -= r_d
        score += d

        kind[r_t] -= 1
        kind[t] += 1
        lk += 1
        r -= 1

        ans = max(ans, score + lk ** 2)

    print(ans)


if __name__ == "__main__":
    main()
