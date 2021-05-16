# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:

    h, w, a, b = map(int, sinput().split())
    ans = 0

    def dfs(pos, room, a, b):
        nonlocal ans
        if pos == h * w:
            ans += 1
            return

        if room >> pos & 1:  # 置かれてる
            dfs(pos + 1, room, a, b)
            return

        if b:  # 1*1
            dfs(pos + 1, room | 1 << pos, a, b - 1)
        if a:
            if pos % w != w - 1 and not room & 1 << (pos + 1):  # 右に置ける
                dfs(pos + 1, room | 1 << pos | 1 << (pos + 1), a - 1, b)
            if pos + w < h * w and not room & 1 << (pos + w):  # 下における
                dfs(pos + 1, room | 1 << pos | 1 << (pos + w), a - 1, b)

    dfs(0, 0, a, b)
    print(ans)


if __name__ == "__main__":
    main()
