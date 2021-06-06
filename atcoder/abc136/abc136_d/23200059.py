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
    ans = [0] * len(s)

    cnt_r = 0
    for r in range(len(s)):
        if s[r] == "L":
            continue
        cnt_r += 1
        if s[r + 1] == "L":
            ans[r] += -(-cnt_r // 2)
            ans[r + 1] += cnt_r // 2
            cnt_r = 0

    cnt_l = 0
    for l in reversed(range(len(s))):
        if s[l] == "R":
            continue
        cnt_l += 1
        if s[l - 1] == "R":
            ans[l] += -(-cnt_l // 2)
            ans[l - 1] += cnt_l // 2
            cnt_l = 0

    print(*ans)


if __name__ == "__main__":
    main()
