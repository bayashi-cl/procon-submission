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
    odd = {"R", "U", "D"}
    even = {"L", "U", "D"}
    s = sinput().strip()
    for i in range(1, len(s) + 1):
        if i % 2 == 1:
            if not s[i - 1] in odd:
                break
        else:
            if not s[i - 1] in even:
                break
    else:
        print("Yes")
        return
    print("No")


if __name__ == "__main__":
    main()
