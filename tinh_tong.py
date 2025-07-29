A = int(input())
B = int(input())

A += 1
B -= 1


A += A & 1
B -= B & 1

tmp = A >> 1
tmp1 = B >> 1
s = (tmp1 - tmp + 1) * (tmp + tmp1)

m6 = A % 6
if m6:
    A += (6 - m6)
B -= B % 6

tmp = A // 6
tmp1 = B // 6
s -= (tmp1 - tmp + 1) * (tmp + tmp1) * 3

print(s)
