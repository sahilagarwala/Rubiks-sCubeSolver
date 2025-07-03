//
// Created by Sahil Agarwal.
//

#ifndef RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
#define RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H

#include "bits/stdc++.h"
using namespace std;

/**
 * @brief Abstract base class for Rubik's Cube representations.
 * 
 * This class defines a common interface and shared functionality
 * for multiple models of the Rubik’s Cube (1D, 3D, Bitset, etc.).
 * 
 * Derived classes must implement the pure virtual methods.
 * All cube-solving algorithms (BFS, DFS, IDA*) operate through this base class.
 * 
 * The purpose of this design is to benchmark and compare different
 * cube representations for performance and clarity.
 */
class RubiksCube {
public:
    // Virtual destructor for proper cleanup of derived classes
    virtual ~RubiksCube() = default;

    // Enum to represent each face of the Rubik's Cube
    enum class FACE {
        UP,
        LEFT,
        FRONT,
        RIGHT,
        BACK,
        DOWN
    };

    // Enum to represent each color on the cube
    enum class COLOR {
        WHITE,
        GREEN,
        RED,
        BLUE,
        ORANGE,
        YELLOW
    };

    // Enum to represent all 18 basic Rubik's Cube moves
    enum class MOVE {
        L, LPRIME, L2,
        R, RPRIME, R2,
        U, UPRIME, U2,
        D, DPRIME, D2,
        F, FPRIME, F2,
        B, BPRIME, B2
    };

    /**
     * @brief Get the color of a specific cell on a given face.
     * 
     * If the face is pointing toward you:
     * - Rows are indexed top to bottom
     * - Columns are indexed left to right
     * - Indexing is 0-based
     */
    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;

    /**
     * @brief Get the first character of the color (e.g., 'G' for GREEN)
     */
    static char getColorLetter(COLOR color);

    /**
     * @brief Check whether the cube is currently in the solved state.
     */
    virtual bool isSolved() const = 0;

    /**
     * @brief Convert a move to its standard string representation.
     * Example: MOVE::RPRIME → "R'"
     */
    static string getMove(MOVE ind);

    /**
     * @brief Print the cube in a flattened planar format.
     * 
     * Layout structure:
     *         U
     *     L F R B
     *         D
     * 
     * Visual guide:
     * 
     *         W W W
     *         W W W
     *         W W W
     * 
     * G G G   R R R   B B B   O O O
     * G G G   R R R   B B B   O O O
     * G G G   R R R   B B B   O O O
     * 
     *         Y Y Y
     *         Y Y Y
     *         Y Y Y
     * 
     * Indexing Guide:
     *   b = both row and column
     *   r = row only
     *   c = column only
     */
    void print() const;

    /**
     * @brief Shuffle the cube randomly with a given number of moves.
     * 
     * @param times Number of moves to apply
     * @return Vector of moves applied
     */
    vector<MOVE> randomShuffleCube(unsigned int times);

    /**
     * @brief Perform a single move on the cube
     * 
     * @param ind Move to perform (e.g., MOVE::R)
     * @return Reference to the updated cube object
     */
    RubiksCube& move(MOVE ind);

    /**
     * @brief Apply the inverse of a move
     * 
     * @param ind Move to invert (e.g., R → R', R2 → R2)
     * @return Reference to the updated cube object
     */
    RubiksCube& invert(MOVE ind);

    // Pure virtual functions for all 18 moves
    virtual RubiksCube& f()      = 0;
    virtual RubiksCube& fPrime()= 0;
    virtual RubiksCube& f2()     = 0;

    virtual RubiksCube& u()      = 0;
    virtual RubiksCube& uPrime()= 0;
    virtual RubiksCube& u2()     = 0;

    virtual RubiksCube& l()      = 0;
    virtual RubiksCube& lPrime()= 0;
    virtual RubiksCube& l2()     = 0;

    virtual RubiksCube& r()      = 0;
    virtual RubiksCube& rPrime()= 0;
    virtual RubiksCube& r2()     = 0;

    virtual RubiksCube& d()      = 0;
    virtual RubiksCube& dPrime()= 0;
    virtual RubiksCube& d2()     = 0;

    virtual RubiksCube& b()      = 0;
    virtual RubiksCube& bPrime()= 0;
    virtual RubiksCube& b2()     = 0;

    /**
     * @brief Get the string representation of a cube corner (for debugging or hashing)
     */
    string getCornerColorString(uint8_t ind) const;

    /**
     * @brief Get the corner index (used in bitset and other compressed models)
     */
    uint8_t getCornerIndex(uint8_t ind) const;

    /**
     * @brief Get the corner orientation
     */
    uint8_t getCornerOrientation(uint8_t ind) const;
};

#endif // RUBIKS_CUBE_SOLVER_RUBIKSCUBE_H
