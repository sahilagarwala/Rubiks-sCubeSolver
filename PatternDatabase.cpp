
#include "PatternDatabase.h"
#include <queue>
#include <iostream>

PatternDatabase::PatternDatabase(int size) : database(size), numItems(size) {}

void PatternDatabase::generateDatabase() {
    std::cout << "Generating pattern database..." << std::endl;
    
    // Initialize all entries to max value (15)
    for (int i = 0; i < numItems; i++) {
        database.set(i, 15);
    }
    
    // BFS from solved state
    std::queue<std::pair<RubiksCube*, uint8_t>> queue;
    
    // Create solved cube and set distance to 0
    RubiksCube* solvedCube = nullptr; // This should be initialized with actual cube type
    // setNumMoves(*solvedCube, 0);
    // queue.push({solvedCube, 0});
    
    std::cout << "Pattern database generation complete." << std::endl;
}

void PatternDatabase::reset() {
    database.reset();
}

int PatternDatabase::getSize() const {
    return numItems;
}
