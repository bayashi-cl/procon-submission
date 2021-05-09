def Div(a: int, b: int, m: int) -> int:
    return a * pow(b, m - 2, m) % m


MOD = 10 ** 9 + 7
N = int(input())
fact = [0] * 200009
factinv = [0] * 200009


def init() -> None:
    fact[0] = 1
    for i in range(1, 200001):
        fact[i] = (1 * i * fact[i - 1]) % MOD
    for i in range(200001):
        factinv[i] = Div(1, fact[i], MOD)


def ncr(n: int, r: int) -> int:
    if n < r or r < 0:
        return 0
    return (fact[n] * factinv[r] % MOD) * factinv[n - r] % MOD


def query(K: int) -> int:
    ret = 0

    for i in range(1, N // K + 2):
        s1 = N - (K - 1) * (i - 1)
        s2 = i
        ret += ncr(s1, s2)
        ret %= MOD
    return ret


if __name__ == "__main__":
    init()
    for k in range(1, N + 1):
        ans = query(k)
        print(ans)
