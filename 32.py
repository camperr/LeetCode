def func(s):
    l_cnt = 0
    r_cnt = 0
    i = 0
    res = 0
    size = len(s)
    for i in range(size):
        if s[i] == ')': r_cnt += 1
        else: l_cnt += 1
        if r_cnt > l_cnt or i == size - 1:
            res = max(res, min(l_cnt, r_cnt) * 2)
            l_cnt = 0
            r_cnt = 0
    return res

if __name__ == '__main__':
    s = '()())(()(()))'
    print(func(s))