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
    s = sinput().strip()
    k = int(sinput())
    substr = set()
    for i in range(len(s)):
        for j in range(1, k + 1):
            substr.add(s[i : i + j])
    sub_list = list(substr)
    sub_list.sort()
    print(sub_list[k - 1])


if __name__ == "__main__":
    main()
