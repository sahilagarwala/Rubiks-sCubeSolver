#include "RubiksCube.h"

class RubiksCubeBitboard : public RubiksCube {

private:
    uint64_t solved_side_config[6]{};

    int arr[3][3] = {{0, 1, 2},
                     {7, 8, 3},
                     {6, 5, 4}};

    uint64_t one_8 = (1 << 8) - 1, one_24 = (1 << 24) - 1;

    void rotateFace(int ind) {
        uint64_t side = bitboard[ind];
        side = side >> (8 * 6);
        bitboard[ind] = (bitboard[ind] << 16) | (side);
    }

    void rotateSide(int s1, int s1_1, int s1_2, int s1_3, int s2, int s2_1, int s2_2, int s2_3) {
        uint64_t clr1 = (bitboard[s2] & (one_8 << (8 * s2_1))) >> (8 * s2_1);
        uint64_t clr2 = (bitboard[s2] & (one_8 << (8 * s2_2))) >> (8 * s2_2);
        uint64_t clr3 = (bitboard[s2] & (one_8 << (8 * s2_3))) >> (8 * s2_3);

        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_1))) | (clr1 << (8 * s1_1));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_2))) | (clr2 << (8 * s1_2));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_3))) | (clr3 << (8 * s1_3));
    }

public:
    uint64_t bitboard[6]{};

    RubiksCubeBitboard() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 9; j++) {
                bitboard[i] |= (uint64_t(i) << (8 * j));
            }
            solved_side_config[i] = bitboard[i];
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        int idx = arr[row][col];
        uint64_t color = (bitboard[(int)face] >> (8 * idx)) & one_8;
        return COLOR(color);
    }

    bool isSolved() const override {
        for (int i = 0; i < 6; i++) {
            if (solved_side_config[i] != bitboard[i]) return false;
        }
        return true;
    }

    RubiksCube &u() override {
        this->rotateFace(0);
        uint64_t temp = bitboard[2] & one_24;
        bitboard[2] = (bitboard[2] & ~one_24) | (bitboard[3] & one_24);
        bitboard[3] = (bitboard[3] & ~one_24) | (bitboard[4] & one_24);
        bitboard[4] = (bitboard[4] & ~one_24) | (bitboard[1] & one_24);
        bitboard[1] = (bitboard[1] & ~one_24) | temp;
        return *this;
    }

    RubiksCube &uPrime() override {
        this->u(); this->u(); this->u();
        return *this;
    }

    RubiksCube &u2() override {
        this->u(); this->u();
        return *this;
    }

    RubiksCube &l() override {
        this->rotateFace(1);
        uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 0))) >> (8 * 0);
        uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);
        uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 7))) >> (8 * 7);
        this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
        this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
        this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);
        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 0))) | (clr1 << (8 * 0));
        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 7))) | (clr3 << (8 * 7));
        return *this;
    }

    RubiksCube &lPrime() override {
        this->l(); this->l(); this->l();
        return *this;
    }

    RubiksCube &l2() override {
        this->l(); this->l();
        return *this;
    }

    RubiksCube &f() override {
        this->rotateFace(2);
        uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);
        uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 5))) >> (8 * 5);
        uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 6))) >> (8 * 6);
        this->rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
        this->rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
        this->rotateSide(5, 0, 1, 2, 3, 6, 7, 0);
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    }

    RubiksCube &fPrime() override {
        this->f(); this->f(); this->f();
        return *this;
    }

    RubiksCube &f2() override {
        this->f(); this->f();
        return *this;
    }

    RubiksCube &r() override {
        this->rotateFace(3);
        uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);
        uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 1))) >> (8 * 1);
        uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 0))) >> (8 * 0);
        this->rotateSide(0, 2, 1, 0, 2, 2, 1, 0);
        this->rotateSide(2, 2, 1, 0, 5, 2, 1, 0);
        this->rotateSide(5, 2, 1, 0, 4, 6, 7, 8);
        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    }

    RubiksCube &rPrime() override {
        this->r(); this->r(); this->r();
        return *this;
    }

    RubiksCube &r2() override {
        this->r(); this->r();
        return *this;
    }

    RubiksCube &b() override {
        this->rotateFace(4);
        uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 0))) >> (8 * 0);
        uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 7))) >> (8 * 7);
        uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 6))) >> (8 * 6);
        this->rotateSide(0, 0, 7, 6, 3, 2, 3, 4);
        this->rotateSide(3, 2, 3, 4, 5, 8, 1, 2);
        this->rotateSide(5, 8, 1, 2, 1, 6, 7, 0);
        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    }

    RubiksCube &bPrime() override {
        this->b(); this->b(); this->b();
        return *this;
    }

    RubiksCube &b2() override {
        this->b(); this->b();
        return *this;
    }

    RubiksCube &d() override {
        this->rotateFace(5);
        uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 4))) >> (8 * 4);
        uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 5))) >> (8 * 5);
        uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);
        this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
        this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
        this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 4))) | (clr1 << (8 * 4));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 5))) | (clr2 << (8 * 5));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));
        return *this;
    }

    RubiksCube &dPrime() override {
        this->d(); this->d(); this->d();
        return *this;
    }

    RubiksCube &d2() override {
        this->d(); this->d();
        return *this;
    }

    bool operator==(const RubiksCubeBitboard &r1) const {
        for (int i = 0; i < 6; i++) {
            if (bitboard[i] != r1.bitboard[i]) return false;
        }
        return true;
    }

    RubiksCubeBitboard &operator=(const RubiksCubeBitboard &r1) {
        for (int i = 0; i < 6; i++) {
            bitboard[i] = r1.bitboard[i];
        }
        return *this;
    }
};

struct HashBitboard {
    size_t operator()(const RubiksCubeBitboard &r1) const {
        uint64_t hash_val = 0;
        for (int i = 0; i < 6; i++) {
            hash_val ^= r1.bitboard[i] + 0x9e3779b9 + (hash_val << 6) + (hash_val >> 2);
        }
        return hash_val;
    }
};