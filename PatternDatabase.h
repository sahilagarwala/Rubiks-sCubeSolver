//RubiksCube
#ifndef PATTERNDATABASE_H
#define PATTERNDATABASE_H

#include "NibbleArray.h"
#include "RubiksCube.h"
#include <unordered_set>

class PatternDatabase {
protected:
    NibbleArray database;
    int numItems;
    
public:
    PatternDatabase(int size);
    virtual ~PatternDatabase() = default;
    
    virtual uint8_t getNumMoves(const RubiksCube& cube) = 0;
    virtual bool setNumMoves(const RubiksCube& cube, uint8_t numMoves) = 0;
    virtual uint8_t getNumMoves(uint32_t index) = 0;
    virtual bool setNumMoves(uint32_t index, uint8_t numMoves) = 0;
    
    void generateDatabase();
    void reset();
    int getSize() const;
};

#endif
