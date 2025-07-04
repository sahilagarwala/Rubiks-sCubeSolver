
#include "CornerPatternDatabase.h"
#include "RubiksCube1dArray.cpp"
#include <iostream>

CornerPatternDatabase::CornerPatternDatabase() : PatternDatabase(88179840) {
    // 8! * 3^7 = 40320 * 2187 = 88,179,840 possible corner configurations
}

std::vector<int> CornerPatternDatabase::getCornerPositions(const RubiksCube& cube) {
    // This is a simplified version - actual implementation would extract corner positions
    // from the cube state based on the specific representation
    return std::vector<int>(8, 0);
}

std::vector<int> CornerPatternDatabase::getCornerOrientations(const RubiksCube& cube) {
    // This is a simplified version - actual implementation would extract corner orientations
    // from the cube state based on the specific representation
    return std::vector<int>(8, 0);
}

uint32_t CornerPatternDatabase::getCornerIndex(const RubiksCube& cube) {
    std::vector<int> positions = getCornerPositions(cube);
    std::vector<int> orientations = getCornerOrientations(cube);
    
    uint32_t positionIndex = permIndexer.rank(positions);
    
    // Calculate orientation index (base-3 number)
    uint32_t orientationIndex = 0;
    uint32_t multiplier = 1;
    for (int i = 0; i < 7; i++) { // Only 7 orientations are independent
        orientationIndex += orientations[i] * multiplier;
        multiplier *= 3;
    }
    
    return positionIndex * 2187 + orientationIndex; // 2187 = 3^7
}

uint8_t CornerPatternDatabase::getNumMoves(const RubiksCube& cube) {
    uint32_t index = getCornerIndex(cube);
    return database.get(index);
}

bool CornerPatternDatabase::setNumMoves(const RubiksCube& cube, uint8_t numMoves) {
    uint32_t index = getCornerIndex(cube);
    if (database.get(index) > numMoves) {
        database.set(index, numMoves);
        return true;
    }
    return false;
}

uint8_t CornerPatternDatabase::getNumMoves(uint32_t index) {
    return database.get(index);
}

bool CornerPatternDatabase::setNumMoves(uint32_t index, uint8_t numMoves) {
    if (database.get(index) > numMoves) {
        database.set(index, numMoves);
        return true;
    }
    return false;
}

void CornerPatternDatabase::generateDatabase() {
    std::cout << "Generating corner pattern database..." << std::endl;
    
    // Initialize all entries to 15 (max distance)
    for (int i = 0; i < numItems; i++) {
        database.set(i, 15);
    }
    
    // Set solved state distance to 0
    RubiksCube1dArray solvedCube;
    setNumMoves(solvedCube, 0);
    
    // BFS to generate all distances
    std::queue<std::pair<RubiksCube1dArray, uint8_t>> queue;
    queue.push({solvedCube, 0});
    
    int processed = 0;
    while (!queue.empty()) {
        auto current = queue.front();
        queue.pop();
        
        RubiksCube1dArray cube = current.first;
        uint8_t depth = current.second;
        
        if (depth >= 15) continue; // Max depth reached
        
        // Try all 18 moves
        for (int move = 0; move < 18; move++) {
            RubiksCube1dArray newCube = cube;
            newCube.move(RubiksCube::MOVE(move));
            
            if (setNumMoves(newCube, depth + 1)) {
                queue.push({newCube, depth + 1});
            }
        }
        
        processed++;
        if (processed % 100000 == 0) {
            std::cout << "Processed " << processed << " states..." << std::endl;
        }
    }
    
    std::cout << "Corner pattern database generation complete." << std::endl;
}
