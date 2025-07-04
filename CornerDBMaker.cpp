//RubiksCube
#include "CornerDBMaker.h"
#include <fstream>
#include <iostream>

CornerDBMaker::CornerDBMaker() {}

void CornerDBMaker::generateDatabase() {
    std::cout << "Starting corner database generation..." << std::endl;
    database.generateDatabase();
    std::cout << "Corner database generation completed." << std::endl;
}

void CornerDBMaker::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }
    
    // Save database size
    int size = database.getSize();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // Save database contents
    for (int i = 0; i < size; i++) {
        uint8_t value = database.getNumMoves(i);
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    
    file.close();
    std::cout << "Database saved to " << filename << std::endl;
}

bool CornerDBMaker::loadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        return false;
    }
    
    // Read database size
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    if (size != database.getSize()) {
        std::cerr << "Error: Database size mismatch." << std::endl;
        file.close();
        return false;
    }
    
    // Read database contents
    for (int i = 0; i < size; i++) {
        uint8_t value;
        file.read(reinterpret_cast<char*>(&value), sizeof(value));
        database.setNumMoves(i, value);
    }
    
    file.close();
    std::cout << "Database loaded from " << filename << std::endl;
    return true;
}

CornerPatternDatabase& CornerDBMaker::getDatabase() {
    return database;
}
