import re

def is_digit(s, p):
    if p < 0 or p >= len(s):
        return False
    return '0' <= s[p] <= '9'

def is_int(s, sign_allow = True):
    if len(s) == 0:
        return False
    if s[0] in ('+', '-'):
        if not sign_allow or len(s) == 1:
            return False
        s = s[1:]
    for i in range(len(s)):
        if not is_digit(s, i):
            return False
    return True

def is_decimal(s, sign_allow = True):
    parts = s.split('.')
    if len(s) == 0 or len(parts) > 2:
        return False
    if len(parts) == 1:
        return is_int(s, sign_allow)
    if len(parts) == 2:
        l_int = is_int(parts[0], sign_allow)
        r_int = is_int(parts[1], sign_allow = False)
        l_nul = (parts[0] == '' or parts[0] in ('-', '+'))
        r_nul = (parts[1] == '')
        return (l_int and r_int) or (l_int and r_nul) or (l_nul and r_int)

def solve(numstr):
    ns = numstr.strip()
    ns = re.sub(r'\s+', ' ', ns)
    if len(ns) == 0:
        return False
    
    parts = ns.split('e')
    if len(parts) > 2:
        return False
    if len(parts) == 1:
        return is_decimal(ns, sign_allow = True)
    if len(parts) == 2:
        return is_decimal(parts[0], sign_allow = True) and is_int(parts[1], sign_allow = True)

def main():
    with open('65_test.txt','r') as tf:
        for line in tf:
            print("---------------------")
            case = line[:-1].split('_')
            assert len(case) == 2
            print('test case: ' + case[0])
            print('expect: ' + case[1])
            expect = True if case[1] == 'True' else False
            ans = solve(case[0])
            print('answer: ' + str(ans))
            if ans != expect:
                print('incorrect')
                break
            else:
                print('pass')
        

if __name__ == '__main__':
    main()
