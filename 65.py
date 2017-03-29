import re
def is_positive_int(numstr):
    for c in numstr:
        if c < '0' or c > '9':
            return False
    return True
def solve(numstr):
    ns = numstr.strip()
    ns = re.sub(r'\s+', ' ', ns)
    if len(ns) == 0:
        return False
    
    point_allow = True
    e_allow = True
    
    for i, c in enumerate(ns):
        if c <'0' or c > '9':
            if c not in ('e', '.', '-', '+', ' '):
                return False
            if len(ns) == 1:
                return False
            if c in ('-', '+') and i > 0:
                if ns[i-1] == 'e':
                    return is_positive_int(ns[i+1:])
                else:
                    return False
            if c == ' ':
                if ns[i-1] not in ('-', '+'):
                    return False
            if c == '.':
                if not point_allow or i == 0:
                    return False
                point_allow = False
            if c == 'e':
                if not e_allow or i == 0:
                    return False
                if i < len(ns) - 1 and ns[i+1] not in ('-', '+'):
                    return is_positive_int(ns[i+1:])
                e_allow = False
                point_allow = False
    return True

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
