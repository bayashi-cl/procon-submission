import numpy as np

N = int(input())
arr = np.array(list(map(int, input().split())))
sq_sum = np.sum(arr ** 2)
s = np.sum(arr)
ab = 0
for a in arr:
    s -= a
    ab += a * s

print((N - 1) * sq_sum - (2 * ab))
