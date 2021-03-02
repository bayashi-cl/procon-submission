def ext_gcd(a, b):
    if b:
        d, y, x = ext_gcd(b, a % b)
        y -= (a // b) * x
        return d, x, y
    return a, 1, 0


def crt(a, b, mod1, mod2):
    g, k, _ = ext_gcd(mod1, mod2)
    if (b - a) % g != 0:
        return -1
    k *= (b - a) // g
    ans = mod1 * k + a
    lcm = mod1 * mod2 // g
    return ans % lcm


T = int(input())
for _ in range(T):
    x, y, p, q = map(int, input().split())
    ans = float("inf")
    mod1 = 2 * (x + y)
    mod2 = p + q

    for j in range(p, p + q):
        t = crt(x, j, mod1, mod2)
        if t == -1:
            continue
        ans = min(ans, t)

    for i in range(x, x + y):
        t = crt(i, p, mod1, mod2)
        if t == -1:
            continue
        ans = min(ans, t)

    if ans == float("inf"):
        print("infinity")
    else:
        print(ans)
