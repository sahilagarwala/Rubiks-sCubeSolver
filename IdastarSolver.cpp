
#include "RubiksCube.h"
#include "CornerPatternDatabase.h"
#include <vector>
#include <climits>
#include <iostream>

template <typename T, typename H>
class IdastarSolver {
private:
    T cube;
    CornerPatternDatabase* cornerDB;
    std::vector<RubiksCube::MOVE> solution;
    int maxDepth;
    
    int search(T& currentCube, int depth, int threshold, std::vector<RubiksCube::MOVE>& path);
    int getHeuristic(const T& cube);
    
public:
    IdastarSolver(T& startCube, CornerPatternDatabase* db = nullptr, int maxDepth = 20);
    std::vector<RubiksCube::MOVE> solve();
    void setCornerDatabase(CornerPatternDatabase* db);
};

template <typename T, typename H>
IdastarSolver<T, H>::IdastarSolver(T& startCube, CornerPatternDatabase* db, int maxDepth) 
    : cube(startCube), cornerDB(db), maxDepth(maxDepth) {}

template <typename T, typename H>
void IdastarSolver<T, H>::setCornerDatabase(CornerPatternDatabase* db) {
    cornerDB = db;
}

template <typename T, typename H>
int IdastarSolver<T, H>::getHeuristic(const T& cube) {
    if (cornerDB) {
        return cornerDB->getNumMoves(cube);
    }
    return 0; // No heuristic available
}

template <typename T, typename H>
int IdastarSolver<T, H>::search(T& currentCube, int depth, int threshold, std::vector<RubiksCube::MOVE>& path) {
    int heuristic = getHeuristic(currentCube);
    int f = depth + heuristic;
    
    if (f > threshold) {
        return f;
    }
    
    if (currentCube.isSolved()) {
        solution = path;
        return -1; // Found solution
    }
    
    if (depth >= maxDepth) {
        return INT_MAX;
    }
    
    int minThreshold = INT_MAX;
    
    // Try all 18 possible moves
    for (int moveIndex = 0; moveIndex < 18; moveIndex++) {
        RubiksCube::MOVE move = static_cast<RubiksCube::MOVE>(moveIndex);
        
        // Avoid immediate reversal of the last move
        if (!path.empty()) {
            RubiksCube::MOVE lastMove = path.back();
            if ((moveIndex / 3) == (static_cast<int>(lastMove) / 3)) {
                continue; // Same face as last move
            }
        }
        
        // Make the move
        currentCube.move(move);
        path.push_back(move);
        
        int result = search(currentCube, depth + 1, threshold, path);
        
        if (result == -1) {
            return -1; // Solution found
        }
        
        if (result < minThreshold) {
            minThreshold = result;
        }
        
        // Undo the move
        path.pop_back();
        currentCube.invert(move);
    }
    
    return minThreshold;
}

template <typename T, typename H>
std::vector<RubiksCube::MOVE> IdastarSolver<T, H>::solve() {
    if (cube.isSolved()) {
        return std::vector<RubiksCube::MOVE>();
    }
    
    int threshold = getHeuristic(cube);
    std::cout << "Starting IDA* search with initial threshold: " << threshold << std::endl;
    
    while (threshold <= maxDepth) {
        std::vector<RubiksCube::MOVE> path;
        T tempCube = cube;
        
        std::cout << "Searching with threshold: " << threshold << std::endl;
        
        int result = search(tempCube, 0, threshold, path);
        
        if (result == -1) {
            std::cout << "Solution found!" << std::endl;
            return solution;
        }
        
        if (result == INT_MAX) {
            break; // No solution exists within max depth
        }
        
        threshold = result;
    }
    
    std::cout << "No solution found within depth limit." << std::endl;
    return std::vector<RubiksCube::MOVE>();
}
