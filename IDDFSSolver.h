#ifndef IDDFSSOLVER_H
#define IDDFSSOLVER_H

#include <vector>
#include "RubiksCube.h"
#include "DFSSolver.h"

template<typename T, typename H>
class IDDFSSolver {
private:
    int max_search_depth;
    std::vector<RubiksCube::MOVE> moves;

public:
    T rubiksCube;

    IDDFSSolver(T _rubiksCube, int _max_search_depth = 7) {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    std::vector<RubiksCube::MOVE> solve() {
        for (int i = 1; i <= max_search_depth; i++) {
            DFSSolver<T, H> dfsSolver(rubiksCube, i);
            moves = dfsSolver.solve();
            if (dfsSolver.rubiksCube.isSolved()) {
                rubiksCube = dfsSolver.rubiksCube;
                break;
            }
        }
        return moves;
    }
};

#endif // IDDFSSOLVER_H
#ifndef IDDFSSOLVER_H
#define IDDFSSOLVER_H

#include <vector>
#include "RubiksCube.h"

template<typename T, typename H>
class IDDFSSolver {
private:
    std::vector<RubiksCube::MOVE> moves;
    int max_search_depth;

    bool dfs(int depth, int max_depth, T& cube) {
        if (cube.isSolved()) {
            return true;
        }
        if (depth >= max_depth) {
            return false;
        }

        for (int i = 0; i < 18; i++) {
            auto curr_move = RubiksCube::MOVE(i);
            cube.move(curr_move);
            moves.push_back(curr_move);
            
            if (dfs(depth + 1, max_depth, cube)) {
                return true;
            }
            
            moves.pop_back();
            cube.invert(curr_move);
        }
        return false;
    }

public:
    T rubiksCube;

    IDDFSSolver(T _rubiksCube, int _max_search_depth = 8) {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    std::vector<RubiksCube::MOVE> solve() {
        moves.clear();
        for (int depth = 1; depth <= max_search_depth; depth++) {
            T temp_cube = rubiksCube;
            if (dfs(0, depth, temp_cube)) {
                rubiksCube = temp_cube;
                return moves;
            }
            moves.clear();
        }
        return std::vector<RubiksCube::MOVE>();
    }
};

#endif // IDDFSSOLVER_H
