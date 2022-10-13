from fractions import Fraction

n = int(input())

if n == 2:
    print(1, 2, 1, 1, 2, 1)
elif n == 3:
    print(1, 3, 1, 2, 2, 3)
else:
    print(1, n, 1, n - 1, 1, n - 2)
