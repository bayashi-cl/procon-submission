from math import ceil, sqrt

N = int(input())

s = set()
for a in range(2, ceil(sqrt(N)) + 2):
    for b in range(2, 40):
        ab = a ** b
        if ab > N:
            break
        s.add(ab)
print(N - len(s))
