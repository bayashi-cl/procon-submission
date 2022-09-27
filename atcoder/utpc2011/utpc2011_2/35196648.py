s = input()

ans = 0
pair = {"w": "w", "i": "i", "(": ")", ")": "("}
for i in range((len(s) + 1) // 2):
    if s[-i - 1] != pair[s[i]]:
        ans += 1

print(ans)
