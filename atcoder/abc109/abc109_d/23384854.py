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


def main() -> None:
    h, w = map(int, sinput().split())
    a = [list(map(int, sinput().split())) for _ in range(h)]
    man = []
    for i in range(h):
        for j in range(w - 1):
            if a[i][j] % 2 == 1:
                a[i][j] -= 1
                a[i][j + 1] += 1
                man.append((i + 1, j + 1, i + 1, j + 2))

    for i in range(h - 1):
        if a[i][-1] % 2 == 1:
            a[i][-1] -= 1
            a[i + 1][-1] += 1
            man.append((i + 1, w, i + 2, w))

    print(len(man))
    for m in man:
        print(*m)


if __name__ == "__main__":
    main()
