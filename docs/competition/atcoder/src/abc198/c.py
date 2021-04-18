#Problem : C - Compass Walking
#Contest : AtCoder - AtCoder Beginner Contest 198
#URL : https:  // atcoder.jp/contests/abc198/tasks/abc198_c
#Memory Limit : 1024 MB
#Time Limit : 2000 ms

import math

R, X, Y = map(int, input().split())
D = math.sqrt(X * X + Y * Y)

if D == R : 
	print(1) 
elif D <= R + R : 
	print(2)
else : 
	print(math.ceil(D / R))
