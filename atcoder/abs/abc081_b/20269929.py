import sys

_ = input()
a = list(map(int, input().split()))
cnt = 0
while True:
    for i, ai in enumerate(a):
        if ai % 2 == 1:
            print(cnt)
            sys.exit(0)
        a[i] = ai / 2
    cnt += 1
