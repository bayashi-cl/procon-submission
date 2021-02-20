s = input()

while len(s) != 0:
    try:
        if s[-5:] == "dream" or s[-5:] == "erase":
            s = s[:-5]
        elif s[-6:] == "eraser":
            s = s[:-6]
        elif s[-7:] == "dreamer":
            s = s[:-7]
        else:
            print("NO")
            break
    except IndexError:
        print("NO")
        break
else:
    print("YES")
