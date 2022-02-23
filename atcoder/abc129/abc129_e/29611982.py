import sys


MOD7 = 1000000007


class modint:
    @staticmethod
    def mod():
        return MOD7

    def __init__(self, v=0):
        x = v % MOD7
        if x < 0:
            x += MOD7
        self.__v = x

    def val(self):
        return self.__v

    def __add__(x, y):
        ret = modint()
        ret.__v = x.__v + y.__v
        if ret.__v >= MOD7:
            ret.__v -= MOD7
        return ret

    def __mul__(x, y):
        ret = modint()
        ret.__v = x.__v * y.__v % MOD7
        return ret


def main() -> None:
    l = input()
    n = len(l)
    dp = [[modint(0) for _ in range(n + 1)] for _ in range(2)]
    dp[0][0] = modint(1)
    for i, li in enumerate(l):
        if li == "0":
            dp[0][i + 1] += dp[0][i]
            dp[1][i + 1] += dp[1][i] * modint(3)
        else:
            dp[0][i + 1] += dp[0][i] * modint(2)
            dp[1][i + 1] += dp[0][i]
            dp[1][i + 1] += dp[1][i] * modint(3)

    print((dp[0][n] + dp[1][n]).val())


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
