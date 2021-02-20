n = int(input())
a = list(map(int, input().split()))
a_s = sorted(a)[::-1]
alice = sum(a_s[::2])
bob = sum(a_s[1::2])
print(alice - bob)
