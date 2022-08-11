n = int(input())
_ = input()
s = set(input().split())

for _ in range(n - 1):
    _ = input()
    t = set()
    for si in input().split():
        if si in s:
            t.add(si)
    s = t

print(len(s))
