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
    x = int(sinput())
    prime = [False] * (2 * x + 1)
    for i in range(2, 2 * x + 1):
        if not prime[i]:
            if i >= x:
                print(i)
                return
            k = 1
            while i * k <= 2 * x:
                prime[i * k] = True
                k += 1
    else:
        raise ValueError


if __name__ == "__main__":
    main()
