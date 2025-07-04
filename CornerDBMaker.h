
#ifndef CORNERDBMAKER_H
#define CORNERDBMAKER_H

#include "CornerPatternDatabase.h"
#include <string>

class CornerDBMaker {
private:
    CornerPatternDatabase database;
    
public:
    CornerDBMaker();
    void generateDatabase();
    void saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    CornerPatternDatabase& getDatabase();
};

#endif
