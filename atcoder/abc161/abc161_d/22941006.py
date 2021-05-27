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
    k = int(sinput())
    if k <= 9:
        print(k)
        return
    # lun = 0
    dp = [[0] * 11 for _ in range(20)]  # i桁 先頭j
    dp[1][:-1] = [1] * 10
    lun_sum = 9
    for i in range(2, 20):
        for j in range(10):
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]
            if j == 0:
                continue
            if lun_sum + dp[i][j] >= k:
                lun_k = lun_sum
                lun_len = i
                lun_top = j
                break
            lun_sum += dp[i][j]
        else:
            continue
        break
    else:
        raise ValueError

    lun = lun_top
    for d in range(lun_len - 1, 0, -1):
        if lun_k + dp[d][lun_top - 1] >= k:
            lun_top = lun_top - 1
            lun = lun * 10 + lun_top
            continue
        lun_k += dp[d][lun_top - 1]

        if lun_k + dp[d][lun_top] >= k:
            lun_top = lun_top
            lun = lun * 10 + lun_top
            continue
        lun_k += dp[d][lun_top]

        lun_top += 1
        lun = lun * 10 + lun_top

    print(lun)


if __name__ == "__main__":
    main()
