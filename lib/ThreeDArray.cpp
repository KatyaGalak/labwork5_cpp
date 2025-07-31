#include "ThreeDArray.h"

using namespace MyThreeDArray;

ThreeDArray ThreeDArray::make_array(uint32_t x, uint32_t y, uint32_t z) {
    return ThreeDArray(x, y, z);
}

bool ThreeDArray::operator==(const ThreeDArray& lhs) const {
    if (sizeX != lhs.sizeX || sizeY != lhs.sizeY || sizeZ != lhs.sizeZ) {
        throw std::logic_error("The sizes of the arrays do not match (they cannot be compared)");
    }

    for (uint32_t x = 0; x < sizeX; ++x) {
        for (uint32_t y = 0; y < sizeY; ++y) {
            for (uint32_t z = 0; z < sizeZ; ++z) {
                if ((*this)[x][y][z] != lhs[x][y][z]) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool ThreeDArray::operator!=(const ThreeDArray& lhs) const {
    return !((*this) == lhs);
}

ThreeDArray& ThreeDArray::operator+=(const int& num) {
    for (uint32_t x = 0; x < sizeX; ++x) {
        for (uint32_t y = 0; y < sizeY; ++y) {
            for (uint32_t z = 0; z < sizeZ; ++z) {
                (*this)[x][y][z] += num;
            }
        }
    }

    return *this;
}

ThreeDArray& ThreeDArray::operator-=(const int& num) {
    return operator+=(-num);
}

ThreeDArray& ThreeDArray::operator=(const ThreeDArray& num) {
    if (sizeX != num.sizeX || sizeY != num.sizeY || sizeZ != num.sizeZ) {
        throw std::logic_error("The sizes of the arrays do not match (they cannot be equal)");
    }

    if (this == &num) {
        return *this;
    }

    for (uint32_t x = 0; x < sizeX; ++x) {
        for (uint32_t y = 0; y < sizeY; ++y) {
            for (uint32_t z = 0; z < sizeZ; ++z) {
                (*this)[x][y][z] = num[x][y][z];
            }
        }
    }

    return *this;
}

ThreeDArray& ThreeDArray::operator+=(const ThreeDArray& num) {
    if (sizeX != num.sizeX || sizeY != num.sizeY || sizeZ != num.sizeZ) {
        throw std::logic_error("The sizes of the arrays do not match (they cannot be folded)");
    }

    for (uint32_t x = 0; x < sizeX; ++x) {
        for (uint32_t y = 0; y < sizeY; ++y) {
            for (uint32_t z = 0; z < sizeZ; ++z) {
                (*this)[x][y][z] += num[x][y][z];
            }
        }
    }

    return *this;
}

ThreeDArray& ThreeDArray::operator-=(const ThreeDArray& num) {
    if (sizeX != num.sizeX || sizeY != num.sizeY || sizeZ != num.sizeZ) {
        throw std::logic_error("The sizes of the arrays do not match (they cannot be folded)");
    }

    for (uint32_t x = 0; x < sizeX; ++x) {
        for (uint32_t y = 0; y < sizeY; ++y) {
            for (uint32_t z = 0; z < sizeZ; ++z) {
                (*this)[x][y][z] -= num[x][y][z];
            }
        }
    }

    return *this;
}

ThreeDArray& ThreeDArray::operator*=(const int& num) {
    for (uint32_t x = 0; x < sizeX; ++x) {
        for (uint32_t y = 0; y < sizeY; ++y) {
            for (uint32_t z = 0; z < sizeZ; ++z) {
                (*this)[x][y][z] *= num;
            }
        }
    }

    return *this;
}

ThreeDArray MyThreeDArray::operator+(const ThreeDArray& lhs, const int& rhs) {
    ThreeDArray ans = ThreeDArray::make_array(lhs.sizeX, lhs.sizeY, lhs.sizeZ);
    ans = lhs;
    ans += rhs;

    return ans;
}

ThreeDArray MyThreeDArray::operator+(const ThreeDArray& lhs, const ThreeDArray& rhs) {
    ThreeDArray ans = ThreeDArray::make_array(lhs.sizeX, lhs.sizeY, lhs.sizeZ);
    ans = lhs;
    ans += rhs;

    return ans;
}

ThreeDArray MyThreeDArray::operator*(const ThreeDArray& lhs, const int& rhs) {
    ThreeDArray ans = ThreeDArray::make_array(lhs.sizeX, lhs.sizeY, lhs.sizeZ);
    ans = lhs;
    ans *= rhs;

    return ans;
}

ThreeDArray MyThreeDArray::operator-(const ThreeDArray& lhs, const int& rhs) {
    ThreeDArray ans = ThreeDArray::make_array(lhs.sizeX, lhs.sizeY, lhs.sizeZ);
    ans = lhs;
    ans -= rhs;

    return ans;
}

ThreeDArray MyThreeDArray::operator-(const ThreeDArray& lhs, const ThreeDArray& rhs) {
    ThreeDArray ans = ThreeDArray::make_array(lhs.sizeX, lhs.sizeY, lhs.sizeZ);
    ans = lhs;
    ans -= rhs;

    return ans;
}

Bit17Number& Bit17Number::operator=(const uint32_t& value) {
    SetValue(value);

    return *this;
}

uint32_t Bit17Number::GetNumber() const {
    uint32_t get_four_byte = (0 << (ThreeDArray::kBitsUint8 * 3))
                             | (static_cast<uint32_t>(*byte_) << (ThreeDArray::kBitsUint8 * 2))
                             | (static_cast<uint32_t>(*(byte_ + 1)) << (ThreeDArray::kBitsUint8))
                             | (*(byte_ + 2));

    for (int i = ThreeDArray::kBitsUint8; i < ThreeDArray::kBitsUint8 + bit_offset_; ++i) {
        get_four_byte = get_four_byte & (~(1U << (ThreeDArray::kBitUint32 - i - 1)));
    }

    get_four_byte = get_four_byte >> (ThreeDArray::kBitsUint8 - bit_offset_ - 1);

    return get_four_byte;
}

void Bit17Number::SetValue(const uint32_t& value) {
    for (int32_t i = ThreeDArray::kBitUint32 - 1, j = 0; j < ThreeDArray::kBitsNumber; --i, ++j) {
        if (j <= bit_offset_) {
            (*(byte_ + 2)) = ((*(byte_ + 2)) & (~(1U << (ThreeDArray::kBitsUint8 - (bit_offset_ - j) - 1))));
        } else if(j > bit_offset_ && j <= bit_offset_ + ThreeDArray::kBitsUint8) {
            (*(byte_ + 1)) = (*(byte_ + 1)) & (~(1U << ((j - bit_offset_ - 1) % ThreeDArray::kBitsUint8)));
        } else {
            (*byte_) = (*byte_) & (~(1U << ((j - bit_offset_ - 1) % ThreeDArray::kBitsUint8)));
        }
    }

    for (int32_t i = ThreeDArray::kBitUint32 - 1, j = 0; j < ThreeDArray::kBitsNumber; --i, ++j) {
        if ((value >> (ThreeDArray::kBitUint32 - i - 1)) & 1) {
            if (j <= bit_offset_) {
                (*(byte_ + 2)) = ((*(byte_ + 2)) | (1U << (ThreeDArray::kBitsUint8 - (bit_offset_ - j) - 1)));
            } else if(j > bit_offset_ && j <= bit_offset_ + ThreeDArray::kBitsUint8) {
                (*(byte_ + 1)) = (*(byte_ + 1)) | (1U << ((j - bit_offset_ - 1) % ThreeDArray::kBitsUint8));
            } else {
                (*byte_) = (*byte_) | (1U << ((j - bit_offset_ - 1) % ThreeDArray::kBitsUint8));
            }
        }
    }
}

Bit17Number& Bit17Number::operator=(const Bit17Number& rhs) {
    if (this == &rhs) {
        return *this;
    }

    uint32_t value = rhs.GetNumber();
    SetValue(value);

    return *this;
}

bool Bit17Number::operator==(const Bit17Number& rhs) const {
    return GetNumber() == rhs.GetNumber();
}

bool Bit17Number::operator==(const uint32_t& rhs) const {
    return GetNumber() == rhs;
}

bool Bit17Number::operator!=(const Bit17Number& rhs) const {
    return GetNumber() != rhs.GetNumber();
}
bool Bit17Number::operator!=(const uint32_t& rhs) const {
    return GetNumber() != rhs;
}

Bit17Number& Bit17Number::operator+=(const int& num) {
    SetValue(GetNumber() + num);

    return *this;
}

Bit17Number& Bit17Number::operator+=(const Bit17Number& num) {
    SetValue(GetNumber() + num.GetNumber());

    return *this;
}

Bit17Number& Bit17Number::operator-=(const int& num) {
    SetValue(GetNumber() - num);

    return *this;
}

Bit17Number& Bit17Number::operator-=(const Bit17Number& num) {
    SetValue(GetNumber() - num.GetNumber());

    return *this;
}

Bit17Number& Bit17Number::operator*=(const int& num) {
    SetValue(GetNumber() * num);

    return *this;
}

Bit17Number& Bit17Number::operator*=(const Bit17Number& num) {
    SetValue(GetNumber() * num.GetNumber());

    return *this;
}

Bit17Number OneDArray::operator[](uint32_t ind_z) const {
    if (ind_z >= sizeZ) {
        throw std::logic_error("An element with such an index on the Y axis goes beyond the array");
    }

    return Bit17Number(byte_ + (ind_z * ThreeDArray::kBitsNumber) / ThreeDArray::kBitsUint8 + (x + y + ind_z) / ThreeDArray::kBitsUint8,
                       (bit_offset_ + ind_z * ThreeDArray::kBitsNumber) % ThreeDArray::kBitsUint8);
}

OneDArray TwoDArray::operator[](uint32_t ind_y) const {
    if (ind_y >= sizeY) {
        throw std::logic_error("An element with such an index on the Y axis goes beyond the array");
    }
    return OneDArray(byte_ + (ind_y * sizeZ * ThreeDArray::kBitsNumber) / ThreeDArray::kBitsUint8,
                     (bit_offset_ + ind_y * sizeZ * ThreeDArray::kBitsNumber) % ThreeDArray::kBitsUint8, sizeZ, x, ind_y * sizeZ);
}
