//RubiksCube
#ifndef PERMUTATIONINDEXER_H
#define PERMUTATIONINDEXER_H

#include <vector>

template <int N, int K>
class PermutationIndexer {
private:
    std::vector<int> factorials;
    
public:
    PermutationIndexer();
    int rank(const std::vector<int>& perm) const;
    std::vector<int> unrank(int index) const;
    int numItems() const { return N; }
    int numPositions() const { return K; }
    long long getNumPermutations() const;
};

template <int N, int K>
PermutationIndexer<N, K>::PermutationIndexer() {
    factorials.resize(N + 1);
    factorials[0] = 1;
    for (int i = 1; i <= N; i++) {
        factorials[i] = factorials[i - 1] * i;
    }
}

template <int N, int K>
int PermutationIndexer<N, K>::rank(const std::vector<int>& perm) const {
    std::vector<bool> used(N, false);
    int rank = 0;
    
    for (int i = 0; i < K; i++) {
        int count = 0;
        for (int j = 0; j < perm[i]; j++) {
            if (!used[j]) count++;
        }
        rank += count * factorials[N - 1 - i] / factorials[N - K];
        used[perm[i]] = true;
    }
    
    return rank;
}

template <int N, int K>
std::vector<int> PermutationIndexer<N, K>::unrank(int index) const {
    std::vector<int> perm(K);
    std::vector<bool> used(N, false);
    
    for (int i = 0; i < K; i++) {
        int factorial = factorials[N - 1 - i] / factorials[N - K];
        int count = index / factorial;
        index %= factorial;
        
        int j = 0;
        while (count > 0 || used[j]) {
            if (!used[j]) count--;
            j++;
        }
        
        perm[i] = j;
        used[j] = true;
    }
    
    return perm;
}

template <int N, int K>
long long PermutationIndexer<N, K>::getNumPermutations() const {
    return factorials[N] / factorials[N - K];
}

#endif
