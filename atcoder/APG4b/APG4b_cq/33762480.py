s = input()

for op in ("?", "=", "!"):
    if op in s:
        print("error")
        break
else:
    try:
        print(int(eval(s)))
    except ZeroDivisionError:
        print("error")
