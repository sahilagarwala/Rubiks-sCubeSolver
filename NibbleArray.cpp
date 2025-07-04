
#include "NibbleArray.h"

NibbleArray::NibbleArray(int size) : size(size) {
    arr.resize((size + 1) / 2, 0);
}

void NibbleArray::set(int index, uint8_t value) {
    if (index >= size) return;
    
    int arrIndex = index / 2;
    if (index % 2 == 0) {
        arr[arrIndex] = (arr[arrIndex] & 0xF0) | (value & 0x0F);
    } else {
        arr[arrIndex] = (arr[arrIndex] & 0x0F) | ((value & 0x0F) << 4);
    }
}

uint8_t NibbleArray::get(int index) const {
    if (index >= size) return 0;
    
    int arrIndex = index / 2;
    if (index % 2 == 0) {
        return arr[arrIndex] & 0x0F;
    } else {
        return (arr[arrIndex] & 0xF0) >> 4;
    }
}

int NibbleArray::getSize() const {
    return size;
}

void NibbleArray::reset() {
    std::fill(arr.begin(), arr.end(), 0);
}
