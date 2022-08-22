n = int(input())
a = int(input())

for i in range(n):
    op, b_ = input().split()
    b = int(b_)
    if op == "+":
        a += b
    elif op == "-":
        a -= b
    elif op == "*":
        a *= b
    elif op == "/":
        if b == 0:
            print("error")
            break
        if a % b == 0 or a // b >= 0:
            a //= b
        else:
            a = a // b + 1
    else:
        raise ValueError

    print(f"{i+1}:{a}")
