def count_inversions(a):
  res = 0
  counts = [0]*(len(a)+1)
  rank = { v : i+1 for i, v in enumerate(sorted(a)) }
  for x in reversed(a):
    i = rank[x] - 1
    while i:
      res += counts[i]
      i -= i & -i
    i = rank[x]
    while i <= len(a):
      counts[i] += 1
      i += i & -i
  return res
  
  
t = int(input())

for i in range(t):
    n = int(input())
    a = list(map(int,input().split()))
    if (len(set(a)) != len(a)):
        print("YES")
        continue
    if (count_inversions(a) % 2 == 0):
        print("YES")
    else:
        print("NO")    