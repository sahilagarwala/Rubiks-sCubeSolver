
#ifndef MATH_H
#define MATH_H

#include <vector>

class Math {
public:
    static long long factorial(int n);
    static long long nCr(int n, int r);
    static long long nPr(int n, int r);
    static std::vector<std::vector<int>> generatePermutations(int n);
    static std::vector<std::vector<int>> generateCombinations(int n, int r);
};

#endif
