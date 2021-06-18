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
    n, c = map(int, sinput().split())
    sushi = [tuple(map(int, sinput().split())) for _ in range(n)]
    # left -> right
    cal_right = [0] * (n + 1)
    cal_right_ret = [0] * (n + 1)
    cal = 0
    for i in range(1, n + 1):
        x, v = sushi[i - 1]
        cal += v
        cal_right[i] = max(cal_right[i - 1], cal - x)
        cal_right_ret[i] = max(cal_right_ret[i - 1], cal - x * 2)

    cal_left = [0] * (n + 1)
    cal_left_ret = [0] * (n + 1)
    cal = 0
    for i in range(1, n + 1):
        x, v = sushi[-i]
        cal += v
        cal_left[i] = max(cal_left[i - 1], cal - (c - x))
        cal_left_ret[i] = max(cal_left_ret[i - 1], cal - (c - x) * 2)

    ans = 0
    for i in range(n + 1):
        cand1 = cal_right[i] + cal_left_ret[n - i]
        cand2 = cal_left[n - i] + cal_right_ret[i]
        ans = max(ans, cand1, cand2)
    print(ans)


if __name__ == "__main__":
    main()
