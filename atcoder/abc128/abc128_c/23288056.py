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


def bit2set(n: int):
    res = set()
    for i in range(n.bit_length()):
        if 1 << i & n == 0:
            continue
        res.add(i)
    return res


def main() -> None:
    n, m = map(int, sinput().split())
    switch = []
    for _ in range(m):
        k, *si = map(int, sinput().split())
        switch.append(si)
    p = list(map(int, sinput().split()))

    ans = 0
    for i in range(1 << n):
        on = bit2set(i)
        for j in range(m):
            cnt = 0
            for s in switch[j]:
                if s - 1 in on:
                    cnt += 1
            if cnt % 2 != p[j]:
                break
        else:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
