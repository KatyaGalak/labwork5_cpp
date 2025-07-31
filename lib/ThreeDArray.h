#pragma once

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstdint>

namespace MyThreeDArray {
    class Bit17Number {
    private:
        uint8_t* byte_;
        uint8_t bit_offset_;
    public:
        Bit17Number(uint8_t* byte, uint8_t bit_offset) : byte_(byte), bit_offset_(bit_offset) {}

        [[nodiscard]] uint32_t GetNumber() const;

        void SetValue(const uint32_t& value);

        Bit17Number& operator=(const uint32_t& value);
        Bit17Number& operator=(const Bit17Number& rhs);

        bool operator==(const Bit17Number& rhs) const;
        bool operator==(const uint32_t& rhs) const;

        bool operator!=(const Bit17Number& rhs) const;
        bool operator!=(const uint32_t& rhs) const;

        Bit17Number& operator+=(const int& num);
        Bit17Number& operator+=(const Bit17Number& num);

        Bit17Number& operator-=(const int& num);
        Bit17Number& operator-=(const Bit17Number& num);

        Bit17Number& operator*=(const int& num);
        Bit17Number& operator*=(const Bit17Number& num);

        friend std::ostream& operator<<(std::ostream& stream, const Bit17Number& num) {
            stream << num.GetNumber();

            return stream;
        }

        friend std::istream& operator>>(std::istream& stream, Bit17Number number) {
            uint32_t num;
            stream >> num;
            number.SetValue(num);

            return stream;
        }
    };

    class OneDArray {
    private:
        uint8_t* byte_;
        uint8_t bit_offset_;

        uint32_t sizeZ;

        uint32_t x;
        uint32_t y;

    public:
        OneDArray(uint8_t* byte, uint8_t bit_offset, uint32_t z, uint32_t ind_x, uint32_t ind_y) :
                byte_(byte), bit_offset_(bit_offset), sizeZ(z), x(ind_x), y(ind_y) {}

        Bit17Number operator[](uint32_t ind_z) const;
    };

    class TwoDArray {
    private:
        uint8_t* byte_;
        uint8_t bit_offset_;

        uint32_t sizeY;
        uint32_t sizeZ;

        uint32_t x;

    public:
        TwoDArray(uint8_t* byte, uint8_t bit, uint32_t y, uint32_t z, uint32_t ind_x) :
                byte_(byte), bit_offset_(bit), sizeY(y), sizeZ(z), x(ind_x) {}

        OneDArray operator[](uint32_t ind_y) const;
    };

    class ThreeDArray {
    private:
        uint8_t* data_;

        uint32_t sizeX;
        uint32_t sizeY;
        uint32_t sizeZ;

        ThreeDArray(uint32_t x, uint32_t y, uint32_t z)
                : sizeX(x), sizeY(y), sizeZ(z) {
            if (x == 0 || y == 0 || z == 0) {
                throw std::logic_error("The dimension of the array cannot be zero");
            }
            data_ = new uint8_t[(x * y * z * kBitsNumber + kBitsUint8 - 1) / kBitsUint8]{0};
        }

    public:
        static const uint32_t kBitsUint8 = 8;
        static const uint32_t kBitsNumber = 17;
        static const uint32_t kBitUint32 = 32;

        ~ThreeDArray() {
            delete[] data_;
        }

        TwoDArray operator[](uint32_t ind_x) const {
            if (ind_x >= sizeX) {
                throw std::logic_error("An element with such an index on the X axis goes beyond the array");
            }
            return TwoDArray((data_ + (ind_x * sizeY * sizeZ * kBitsNumber) / kBitsUint8),
                             (ind_x * sizeY * sizeZ * kBitsNumber) % kBitsUint8, sizeY,
                             sizeZ, ind_x * sizeY * sizeZ);
        }

        static ThreeDArray make_array(uint32_t x, uint32_t y, uint32_t z);

        ThreeDArray& operator+=(const ThreeDArray& num);
        ThreeDArray& operator+=(const int& num);

        ThreeDArray& operator*=(const int& num);

        ThreeDArray& operator-=(const ThreeDArray& num);
        ThreeDArray& operator-=(const int& num);

        ThreeDArray& operator=(const ThreeDArray& num);
        bool operator==(const ThreeDArray& rhs) const;
        bool operator!=(const ThreeDArray& rhs) const;

        friend ThreeDArray operator+(const ThreeDArray& lhs, const ThreeDArray& rhs);
        friend ThreeDArray operator+(const ThreeDArray& lhs, const int& rhs);

        friend ThreeDArray operator*(const ThreeDArray& lhs, const int& rhs);

        friend ThreeDArray operator-(const ThreeDArray& lhs, const ThreeDArray& rhs);
        friend ThreeDArray operator-(const ThreeDArray& lhs, const int& rhs);
    };

}
