s = input()

if not (s[0].isalpha() and s[-1].isalpha()):
    print("No")
    exit()

try:
    if 100000 <= eval(s[1:-1]) < 1000000:
        print("Yes")
    else:
        print("No")
except Exception:
    print("No")
