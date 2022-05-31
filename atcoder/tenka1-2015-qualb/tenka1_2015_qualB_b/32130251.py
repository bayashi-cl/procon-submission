s = input()
if s == "{}":
    print("dict")
else:
    nest = 0

    for si in s:
        if si == "{":
            nest += 1
        elif si == "}":
            nest -= 1
        elif si == ":" and nest == 1:
            print("dict")
            break
    else:
        print("set")
