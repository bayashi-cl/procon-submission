n=int(input())
m=998244353
a=pow(2,n,m)
for i in range(n+2,2*n+1):a=a*i%m
print(a)