s = input()
if s[::2].islower() and (s[1::2].isupper() or len(s) == 1):
    print("Yes")
else:
    print("No")
