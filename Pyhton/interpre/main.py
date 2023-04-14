import sys


'''
function cube a
init result a
mul result a
mul result a
return result

init result 10
cube result

return result
end_program

->

def cube(a):
    result = a
    result *= a
    result *= a
    return result

result = 10
result = cube(result)

print(result)


'''

def list_to_comma_str(lst):
    strin = ''
    for elem in lst:
        strin += elem
        strin += ','
    strin = strin[:-1]
    return strin
code = ''
def solution(f_in, f_out):
    global code
    insideFunc = False


    for line in f_in:
        if line == 'end_program':
            break
        stuff = line.split()
        if len(stuff) == 0:
            continue
        if (stuff[0] == 'function'):
            insideFunc = True
            func_name = stuff[1]

            strin = 'def ' + func_name + '(' + list_to_comma_str(stuff[2:])  + ')' + ':'
            #print(strin)
            code += strin
            code += '\n'
        else:
            if insideFunc:

                if stuff[0] == 'mul':
                    code += '\t'
                    code += stuff[1] +' *= ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'add':
                    code += '\t'
                    code += stuff[1] +' += ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'sub':
                    code += '\t'
                    code += stuff[1] +' -= ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'div':
                    code += '\t'
                    code += stuff[1] +' //= ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'init':
                    code += '\t'
                    code += stuff[1] +' = ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'return':
                    code += '\t'
                    code += 'return ' + stuff[1]
                    if (len(stuff) != 2):
                        raise Exception(code)
                        #pass
                    code += '\n'
                    insideFunc = False
                else:
                    code += '\t'
                    code += stuff[1] + ' = ' + stuff[0] + '(' + list_to_comma_str(stuff[1:]) + ')'
                    code += '\n'
            else:
                if stuff[0] == 'mul':
                    code += stuff[1] +' *= ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'add':
                    code += stuff[1] +' += ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'sub':
                    code += stuff[1] +' -= ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'div':
                    code += stuff[1] +' //= ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'init':
                    code += stuff[1] +' = ' + stuff[2]
                    code += '\n'
                elif stuff[0] == 'return':
                    code += 'print(' + stuff[1] + ')'
                    code += '\n'
                    break
                else:
                    code += stuff[1] + ' = ' + stuff[0] + '(' + list_to_comma_str(stuff[1:]) + ')'
                    code += '\n'
    #print()
    #print(code)

solution(sys.stdin, sys.stdout)
try:
    exec(code)
except:
    raise Exception(code)


