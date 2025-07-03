#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include <vector>
#include "RubiksCube.h"

template<typename T, typename H>
class DFSSolver {
private:
    std::vector<RubiksCube::MOVE> moves;
    int max_search_depth;

    bool dfs(int dep) {
        if (rubiksCube.isSolved()) return true;
        if (dep > max_search_depth) return false;
        for (int i = 0; i < 18; i++) {
            rubiksCube.move(RubiksCube::MOVE(i));
            moves.push_back(RubiksCube::MOVE(i));
            if (dfs(dep + 1)) return true;
            moves.pop_back();
            rubiksCube.invert(RubiksCube::MOVE(i));
        }
        return false;
    }

public:
    T rubiksCube;

    DFSSolver(T _rubiksCube, int _max_search_depth = 15) {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    std::vector<RubiksCube::MOVE> solve() {
        dfs(1);
        return moves;
    }
};

#endif // DFSSOLVER_H
#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include <vector>
#include <unordered_map>
#include "RubiksCube.h"

template<typename T, typename H>
class DFSSolver {
private:
    std::vector<RubiksCube::MOVE> moves;
    int max_search_depth;

    bool dfs(int depth, T& cube) {
        if (cube.isSolved()) {
            return true;
        }
        if (depth >= max_search_depth) {
            return false;
        }

        for (int i = 0; i < 18; i++) {
            auto curr_move = RubiksCube::MOVE(i);
            cube.move(curr_move);
            moves.push_back(curr_move);
            
            if (dfs(depth + 1, cube)) {
                return true;
            }
            
            moves.pop_back();
            cube.invert(curr_move);
        }
        return false;
    }

public:
    T rubiksCube;

    DFSSolver(T _rubiksCube, int _max_search_depth = 8) {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    std::vector<RubiksCube::MOVE> solve() {
        moves.clear();
        if (dfs(0, rubiksCube)) {
            return moves;
        }
        return std::vector<RubiksCube::MOVE>();
    }
};

#endif // DFSSOLVER_H
