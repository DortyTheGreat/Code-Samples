def getSum(n):
    sum = 0
    for digit in str(n):
        sum += int(digit)
    return sum

n = int(input())
for i in range(n):
    s = input()
    stuff = s.split(',')
    #print(stuff)
    diff = 0
    d = set()
    for i in range(3):
        for j in range(len(stuff[i])):
            if stuff[i][j] in d:
                pass
            else:
                d.add(stuff[i][j])
                diff += 1



    cyp = diff + 64 * (getSum(stuff[3]) + getSum(stuff[4])) + 256 * ( ord(stuff[0][0].lower()) - ord('a') + 1)
    cyp %= (16 * 16 * 16)
    print( (f'{cyp:03x}').upper() )

