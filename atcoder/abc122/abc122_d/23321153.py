# region template
import sys
import typing
from collections import defaultdict
from itertools import product

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def check_c(s: str) -> bool:
    if s[1] == "A" and s[2] == "G":
        return False
    elif s[0] == "A" and s[2] == "G":
        return False
    elif s[0] == "A" and s[1] == "G":
        return False
    elif s[1] == "G" and s[2] == "A":
        return False
    else:
        return True


def check_g(s: str) -> bool:
    if s[1] == "A" and s[2] == "C":
        return False
    else:
        return True


def main() -> None:
    n = int(sinput())
    base = ["A", "C", "G", "T"]
    dp = [defaultdict(int) for _ in range(n + 1)]
    for perm in product(base, repeat=3):
        p = "".join(perm)
        if p in {"AGC", "ACG", "GAC"}:
            dp[3][p] = 0
        else:
            dp[3][p] = 1

    for i in range(3, n):
        for k, v in dp[i].items():
            v %= MOD
            k2 = k[1:]
            dp[i + 1][k2 + "A"] += v
            if check_c(k):
                dp[i + 1][k2 + "C"] += v
            if check_g(k):
                dp[i + 1][k2 + "G"] += v
            dp[i + 1][k2 + "T"] += v

    print(sum(dp[-1].values()) % MOD)


if __name__ == "__main__":
    main()
