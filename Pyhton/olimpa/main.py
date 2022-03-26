a = int(input())

b = (input().split())
list_ = []

carret = abs(int(b[0]))

cou = 1

for i in range(1,len(b)):
    new_ = abs(int(b[i]))

    if new_ == carret:
        cou += 1
    else:
        list_.append((carret,cou))
        carret = new_
        cou = 1

list_.append((carret,cou))

signs = []

conf = 0


for i in range(0,len(list_)):
    signs.append(0)




for i in range(0,len(list_) - 1):

    if list_[i][0] > list_[i+1][0]:

        if signs[i] != 1:
            signs[i] = -1
        else:
            conf = 1

    else:

        if signs[i+1] != -1:
            signs[i+1] = 1
        else:
            conf = 1


if conf == 1:
    print(0)




else:
    ans = 1
    mod = 998244353

    for i in range(0,len(signs)):
        if signs[i] == 0:
            ans *= (list_[i][1]+1)
            ans %= mod


    print(ans)


