x = input()
m = int(input())

if len(x) == 1:
    if int(x) > m:
        print(0)
    else:
        print(1)
    exit()

d = int(max(x))
lower = d
upper = 2 * 10 ** 18


def base2d(base):
    deci = 0
    for i, c in enumerate(x[::-1]):
        deci += int(c) * (base ** i)
    return deci


while upper - lower > 1:
    mid = (lower + upper) // 2
    if base2d(mid) <= m:
        lower = mid
    else:
        upper = mid
print(lower - d)
