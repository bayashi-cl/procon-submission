# region template
import sys
import typing

from scipy import special

sys.setrecursionlimit(10 ** 9)
sinput: typing.Callable[..., str] = sys.stdin.readline
INF: typing.Final[float] = float("inf")
MOD: typing.Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    s = sinput().strip()
    need = []
    ban = []
    for i in range(10):
        if s[i] == "o":
            need.append(str(i))
        elif s[i] == "x":
            ban.append(str(i))

    def judge(s) -> bool:
        for n in need:
            if n not in s:
                return False
        for b in ban:
            if b in s:
                return False
        return True

    ans = 0
    for i in range(10000):
        si = str(i).zfill(4)
        if judge(si):
            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
