from __future__ import annotations


def add(a, b):
    if isinstance(a, int):
        return a + b
    elif isinstance(a, list):
        return [ai + bi for ai, bi in zip(a, b)]


def sub(a, b):
    if isinstance(a, int):
        return a - b
    elif isinstance(a, list):
        return [ai - bi for ai, bi in zip(a, b)]


def out(a):
    if isinstance(a, int):
        print(a)
    else:
        print("[ " + " ".join(map(str, a)) + " ]")


op = {"+": add, "-": sub}


def split(s: str) -> list[str]:
    res = []
    prev = 0
    for i, si in enumerate(s):
        if si == "+" or si == "-":
            res.append(s[prev:i].strip())
            res.append(si)
            prev = i + 1
    res.append(s[prev : len(s)].strip())
    return res


var = dict()


def eval_item(item: str):
    if item.isdigit():
        return int(item)
    elif item[0] == "[":
        assert item[-1] == "]"
        return [eval_item(i.strip()) for i in item[1:-1].split(",")]
    else:
        return var[item]


def calc(formula: str):
    items = split(formula)
    res = eval_item(items[0])
    for i in range(1, len(items), 2):
        res = op[items[i]](res, eval_item(items[i + 1]))
    return res


n = int(input())
for _ in range(n):
    order = input()[:-1].strip()
    if order.startswith("print"):
        formula = order[10:]
        out(calc(formula))
    else:
        formula = order[4:]
        var[formula[0]] = calc(formula[4:])
