from collections import Counter
class Point(object):
    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b
def gcd(a, b):
    return a if b == 0 else gcd(b, a%b)

def simplify(a, b):
    if a == 0:
        return (0, 1)
    if b == 0:
        return (1, 0)
    g = gcd(a, b)
    return (a/g, b/g)
class Solution(object):
    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        pol = {}
        if len(points) == 0:
            return 0
        same_point = [0 for i in range(len(points))]
        for i, pi in enumerate(points):
            for pj in points:
                if pi.x == pj.x and pi.y == pj.y:
                    same_point[i] += 1
        for i, pi in enumerate(points):
            for j, pj in enumerate(points):
                if pi.x != pj.x or pi.y != pj.y:
                    a,b = simplify(pi.x - pj.x, pi.y - pj.y)
                    pol[(i, a, b)] = pol.get((i, a, b), same_point[i]) + 1
                else:
                    pol[(i, 0, 0)] = same_point[i]
                    
        return Counter(pol).most_common(1)[0][1]

def main():
    points = [Point(1, 1), Point(1, 1)]
    print(Solution().maxPoints(points))

if __name__ == '__main__':
    main()