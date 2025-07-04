
#include "math.h"
#include <algorithm>
#include <numeric>

long long Math::factorial(int n) {
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

long long Math::nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    if (r == 0 || r == n) return 1;
    
    r = std::min(r, n - r); // Take advantage of symmetry
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

long long Math::nPr(int n, int r) {
    if (r > n || r < 0) return 0;
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result *= (n - i);
    }
    return result;
}

std::vector<std::vector<int>> Math::generatePermutations(int n) {
    std::vector<int> elements(n);
    std::iota(elements.begin(), elements.end(), 0);
    
    std::vector<std::vector<int>> permutations;
    do {
        permutations.push_back(elements);
    } while (std::next_permutation(elements.begin(), elements.end()));
    
    return permutations;
}

std::vector<std::vector<int>> Math::generateCombinations(int n, int r) {
    std::vector<std::vector<int>> combinations;
    std::vector<bool> selector(n);
    std::fill(selector.end() - r, selector.end(), true);
    
    do {
        std::vector<int> combination;
        for (int i = 0; i < n; i++) {
            if (selector[i]) {
                combination.push_back(i);
            }
        }
        combinations.push_back(combination);
    } while (std::next_permutation(selector.begin(), selector.end()));
    
    return combinations;
}
