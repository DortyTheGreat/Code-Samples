

for A in range(200):
    flag = 1
    for x in range(500):
        for y in range(500):
            if (2*y + x != 70) or (x < y) or (A < x):
                pass
            else:
                flag = 0
    if (flag):
        print(A)


