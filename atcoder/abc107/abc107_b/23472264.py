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
    a = [sinput().strip() for _ in range(h)]
    ans_1 = []
    ans = []
    for ai in zip(*a):
        if "#" in ai:
            ans_1.append(ai)

    for ai_2 in zip(*ans_1):
        if "#" in ai_2:
            ans.append(ai_2)

    for aa in ans:
        print("".join(aa))


if __name__ == "__main__":
    main()
