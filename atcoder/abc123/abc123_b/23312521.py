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
    dish_ = [int(sinput()) for _ in range(5)]
    dish = []
    t = 0
    for d in dish_:
        if d % 10 == 0:
            t += d
        else:
            dish.append(d)

    dish.sort(key=lambda x: x % 10, reverse=True)
    for d in dish:
        if (m := t % 10) != 0:
            t += 10 - m

        t += d
    print(t)


if __name__ == "__main__":
    main()
