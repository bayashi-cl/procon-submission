n, k = map(int, input().split())
a = list(map(int, input().split()))
st = [tuple(map(int, input().split())) for _ in range(n)]
st.sort()

print(k)
i = 0
for _ in range(k):
    while a[-1] == 0:
        a.pop()
    i += len(a)
    print(st[i][0] - 1, 0, st[i][0] - 1, 1)
    a[-1] -= 1
