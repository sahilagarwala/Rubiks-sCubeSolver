//RubiksCube
#ifndef NIBBLEARRAY_H
#define NIBBLEARRAY_H

#include <vector>
#include <cstdint>

class NibbleArray {
private:
    std::vector<uint8_t> arr;
    int size;

public:
    NibbleArray(int size);
    void set(int index, uint8_t value);
    uint8_t get(int index) const;
    int getSize() const;
    void reset();
};

#endif
