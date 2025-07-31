#include <functional>
#include <lib/ThreeDArray.h>

#include <iostream>
#include <numeric>

using namespace MyThreeDArray;

int main() {
    ThreeDArray array_1 = ThreeDArray::make_array(200, 100, 400);
    ThreeDArray array_2 = ThreeDArray::make_array(200, 100, 400);

    std::cin >> array_1[0][9][2];

    std::cout << array_1[0][9][2] << std::endl;

}