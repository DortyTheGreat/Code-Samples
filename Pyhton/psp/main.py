strin = input()

couty = [0,0,0]
def main():
    for c in strin:
        if c == '(':
            couty[0] += 1
        elif c == '[':
            couty[1] += 1
        elif c == '{':
            couty[2] += 1
        elif c == ')':
            couty[0] -= 1
            if couty[0] < 0:
                print('Bruh')
                return
        elif c == ']':
            couty[1] -= 1
            if couty[1] < 0:
                print('Bruh')
                return
        elif c == '}':
            couty[2] -= 1
            if couty[2] < 0:
                print('Bruh')
                return

    if couty[0] != 0 or couty[1] != 0 or couty[2] != 0:
        print('Bruh')
    else:
        print('Nice')

main()