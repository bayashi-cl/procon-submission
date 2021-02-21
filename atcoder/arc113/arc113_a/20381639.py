k = int(input())
ans = 0
for a in range(1, k + 1):
    for b in range(1, k + 1):
        if a * b > k:
            break
        left = 0
        right = int(k / (a * b)) + 1
        while right - left > 1:
            mid = (right + left) // 2
            if a * b * mid <= k:
                left = mid
            else:
                right = mid
        ans += left

print(ans)
