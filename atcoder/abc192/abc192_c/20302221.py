def f(x):
    s_x = sorted(str(x))
    return int("".join(s_x[::-1])) - int("".join(s_x))


n, k = map(int, input().split())
fi = n
for i in range(k):
    fi = f(fi)
print(fi)