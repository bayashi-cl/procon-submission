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
    n, k = map(int, sinput().split())
    a = list(map(int, sinput().split()))

    def f(x: int) -> int:
        res = 0
        for ai in a:
            res += ai ^ x
        return res

    if k == 0:
        print(f(0))
        return

    w = k.bit_length()
    zero = [0] * w
    for ai in a:
        for i in range(w):
            if 1 << i & ai == 0:
                zero[-i - 1] += 1

    ideal = [0] * w
    for i in range(w):
        if n <= 2 * zero[i]:
            ideal[i] = 1

    real = list(map(int, list(format(k, "0b"))))

    smaller = False
    bin_x = []
    for i, r in zip(ideal, real):
        if not smaller:
            if i < r:
                bin_x.append(str(i))
                smaller = True
            else:
                bin_x.append(str(r))
        else:
            bin_x.append(str(i))

    x = int("".join(bin_x), 2)
    print(f(x))


if __name__ == "__main__":
    main()
