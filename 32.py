class Solution(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        res = 0
        size = len(s)
        d = [0 for i in range(size)]
        for i in range(size):
            if i == 0 or s[i] == '(':
                d[i] = 0
            else:
                last = i - d[i - 1] - 1
                if last >= 0 and s[last] == '(':
                    d[i] = d[i - 1] + 2
                    if last >= 1:
                        d[i] += d[last - 1]
                else:
                    d[i] = 0
            res = max(res, d[i])
        
        return res

if __name__ == '__main__':
    s = '())(()))'
    print(func(s))