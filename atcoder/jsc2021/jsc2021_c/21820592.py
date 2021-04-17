# region template
import sys
from typing import Any, Callable

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
# endregion


def make_divisors(n):
    left_divisors, right_divisors = [], []
    i = 1
    while i * i <= n:
        if n % i == 0:
            left_divisors.append(i)
            if i != n // i:
                right_divisors.append(n // i)
        i += 1
    return left_divisors + right_divisors[::-1]


def main() -> None:
    a, b = map(int, sinput().split())
    l = [0] * (b + 1)
    for i in range(a, b + 1):
        div = make_divisors(i)
        for j in div:
            l[j] += 1

    for i in range(b, 0, -1):
        if l[i] >= 2:
            print(i)
            break
    else:
        print(1)


if __name__ == "__main__":
    main()
