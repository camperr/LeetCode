class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        wdict = {}
        wvis = {}
        for w in words:
            wdict[w] = 1 if w not in wdict else wdict[w] + 1
            wvis[w] = 0
        
        wn = len(words)
        n = len(s)
        wl = len(words[0])
        res = []
        
        for i in range(wl):
            j = i
            k = j
            wvis = {w : 0 for w in wdict}
            while k + wl * wn <= n:
                wj = s[j : j + wl]
                if wj not in wdict:
                    while k <= j:
                        wk = s[k : k + wl]
                        if wk in wdict:
                            wvis[wk] -= 1
                        k += wl
                else:
                    wvis[wj] += 1
                    while wvis[wj] > wdict[wj]:
                        wk = s[k : k + wl]
                        if wk in wdict:
                            wvis[wk] -= 1
                        k += wl
                j += wl
                if k + wl * wn == j:
                    res.append(k)    
                print(str(j) + ' ' + str(k))
                
        return res

def main():
    s = 'ababaab'
    words = ['ab', 'ba', 'ba']
    sol = Solution()
    print(sol.findSubstring(s, words))

if __name__ == '__main__':
    main()
