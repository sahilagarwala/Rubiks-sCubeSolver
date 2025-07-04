
#ifndef CORNERPATTERNDATABASE_H
#define CORNERPATTERNDATABASE_H

#include "PatternDatabase.h"
#include "PermutationIndexer.h"
#include "RubiksCube.h"

class CornerPatternDatabase : public PatternDatabase {
private:
    PermutationIndexer<8, 8> permIndexer;
    
    std::vector<int> getCornerPositions(const RubiksCube& cube);
    std::vector<int> getCornerOrientations(const RubiksCube& cube);
    uint32_t getCornerIndex(const RubiksCube& cube);
    
public:
    CornerPatternDatabase();
    
    uint8_t getNumMoves(const RubiksCube& cube) override;
    bool setNumMoves(const RubiksCube& cube, uint8_t numMoves) override;
    uint8_t getNumMoves(uint32_t index) override;
    bool setNumMoves(uint32_t index, uint8_t numMoves) override;
    
    void generateDatabase();
};

#endif
