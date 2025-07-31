#include <lib/ThreeDArray.h>
#include <gtest/gtest.h>
#include <sstream>


using namespace MyThreeDArray;

TEST(TreeDArraySuite, MakeArray) {
    auto arr = ThreeDArray::make_array(2, 1455, 200);
    EXPECT_NO_THROW(arr[1][1400][198]);
}

TEST(TreeDArraySuite, AdditionArray) {
    ThreeDArray array_1 = ThreeDArray::make_array(2, 6, 8);
    ThreeDArray array_2 = ThreeDArray::make_array(2, 6, 8);
    array_1[0][3][6] = 3;
    array_2[0][3][6] = 2;

    array_1[1][3][2] = 130112;
    array_2[1][3][2] = 958;

    ThreeDArray sum = ThreeDArray::make_array(2, 6, 8);
    sum = (array_1 + array_2);
    ASSERT_EQ(sum[0][3][6], 5);
    ASSERT_EQ(sum[1][3][2], 131070);
}

TEST(ThreeDArraySuite, AdditionEquallyArray) {
    ThreeDArray array_1 = ThreeDArray::make_array(2, 6, 8);
    ThreeDArray array_2 = ThreeDArray::make_array(2, 6, 8);
    array_1[0][3][6] = 3;
    array_2[0][3][6] = 2;

    array_1[1][3][2] = 130112;
    array_2[1][3][2] = 958;

    array_1 += array_2;

    ASSERT_EQ(array_1[0][3][6], 5);
    ASSERT_EQ(array_1[1][3][2], 131070);
}

TEST(ThreeDArraySuite, AdditionNumber) {
    ThreeDArray array_1 = ThreeDArray::make_array(2, 6, 8);
    array_1[0][3][6] = 3;
    array_1[1][3][2] = 130112;

    ThreeDArray sum = ThreeDArray::make_array(2, 6, 8);
    sum = array_1 + 6;

    ASSERT_EQ(sum[0][3][6], 9);
    ASSERT_EQ(sum[1][3][2], 130118);
}

TEST(ThreeDArraySuite, AdditionEquallyNumber) {
    ThreeDArray array_1 = ThreeDArray::make_array(2, 6, 8);
    array_1[0][3][6] = 3;
    array_1[1][3][2] = 130112;

    array_1 += 4;

    ASSERT_EQ(array_1[0][3][6], 7);
    ASSERT_EQ(array_1[1][3][2], 130116);
}

TEST(ThreeDArraySuite, SubtractionArray) {
    ThreeDArray array_1 = ThreeDArray::make_array(3, 4, 5);
    ThreeDArray array_2 = ThreeDArray::make_array(3, 4, 5);

    array_1[2][3][4] = 123454;
    array_2[2][3][4] = 12;

    array_1[1][3][2] = 1301;
    array_2[1][3][2] = 958;

    ThreeDArray sub = ThreeDArray::make_array(3, 4, 5);
    sub = array_1 - array_2;

    ASSERT_EQ(sub[2][3][4], 123442);
    ASSERT_EQ(sub[1][3][2], 343);
}

TEST(ThreeDArraySuite, SubtractionEquallyArray) {
    ThreeDArray array_1 = ThreeDArray::make_array(3, 4, 5);
    ThreeDArray array_2 = ThreeDArray::make_array(3, 4, 5);

    array_1[0][2][0] = 13101;
    array_2[0][2][0] = 12010;

    array_1[1][2][4] = 156;
    array_2[1][2][4] = 121;

    array_1 -= array_2;

    ASSERT_EQ(array_1[0][2][0], 1091);
    ASSERT_EQ(array_1[1][2][4], 35);
}

TEST(ThreeDArraySuite, SubtractionNumber) {
    ThreeDArray array_1 = ThreeDArray::make_array(1, 4, 15);

    for (int x = 0; x < 1; ++x) {
        for (int y = 0; y < 4; ++y) {
            for (int z = 0; z < 15; ++z) {
                array_1[x][y][z] = 3455;
            }
        }
    }

    array_1[0][3][12] = 34554;
    array_1[0][0][4] = 1224;

    ThreeDArray sub = ThreeDArray::make_array(1, 4, 15);
    sub = array_1 - 1224;

    ASSERT_EQ(sub[0][3][12], 33330);
    ASSERT_EQ(sub[0][0][4], 0);
    ASSERT_EQ(sub[0][3][14], 2231);
}

TEST(ThreeDArraySuite, SubtractionEquallyNumber) {
    ThreeDArray array_1 = ThreeDArray::make_array(1, 2, 18);

    for (int x = 0; x < 1; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 18; ++z) {
                array_1[x][y][z] = 12341;
            }
        }
    }

    array_1[0][1][12] = 9809;
    array_1[0][0][14] = 130112;

    array_1 -= 604;

    ASSERT_EQ(array_1[0][1][12], 9205);
    ASSERT_EQ(array_1[0][0][14], 129508);
    ASSERT_EQ(array_1[0][0][0], 11737);
}

TEST(ThreeDArraySuite, MultiplicationNumber) {
    ThreeDArray array_1 = ThreeDArray::make_array(2, 11, 6);
    array_1[0][6][5] = 3;

    array_1[1][0][3] = 65056;

    ThreeDArray mlt = ThreeDArray::make_array(2, 11, 6);
    mlt = array_1 * 2;

    ASSERT_EQ(mlt[0][6][5], 6);
    ASSERT_EQ(mlt[1][0][3], 130112);
}

TEST(ThreeDArraySuite, MultiplicationEquallyNumber) {
    ThreeDArray array_1 = ThreeDArray::make_array(2, 11, 6);
    array_1[0][6][5] = 3;

    array_1[1][0][3] = 65056;

    array_1 *= 2;
    ASSERT_EQ(array_1[0][6][5], 6);
    ASSERT_EQ(array_1[1][0][3], 130112);
}

TEST(ThreeDArraySuite, Equivalence) {
    ThreeDArray array_1 = ThreeDArray::make_array(1, 1, 19);
    ThreeDArray array_2 = ThreeDArray::make_array(1, 1, 19);

    for (int x = 0; x < 1; ++x) {
        for (int y = 0; y < 1; ++y) {
            for (int z = 0; z < 19; ++z) {
                array_1[x][y][z] = 87533;
            }
        }
    }

    for (int x = 0; x < 1; ++x) {
        for (int y = 0; y < 1; ++y) {
            for (int z = 0; z < 19; ++z) {
                array_2[x][y][z] = 87444;
            }
        }
    }
    array_2 += 89;

    ASSERT_TRUE(array_1 == array_2);
}

TEST(ThreeDArraySuite, NotEquivalence) {
    ThreeDArray array_1 = ThreeDArray::make_array(2, 10, 4);
    ThreeDArray array_2 = ThreeDArray::make_array(2, 10, 4);

    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 10; ++y) {
            for (int z = 0; z < 4; ++z) {
                array_1[x][y][z] = 87533;
            }
        }
    }

    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 10; ++y) {
            for (int z = 0; z < 4; ++z) {
                array_2[x][y][z] = 87444;
            }
        }
    }

    ASSERT_TRUE(array_1 != array_2);
    ASSERT_EQ(array_1[1][3][0], 87533);
    ASSERT_EQ(array_2[1][4][3], 87444);
}

TEST(ThreeDArraySuite, Assignment) {
    ThreeDArray array_1 = ThreeDArray::make_array(2, 6, 1);
    ThreeDArray array_2 = ThreeDArray::make_array(2, 6, 1);
    //ThreeDArray array_3 = ThreeDArray::make_array(2, 6, 139);

    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 6; ++y) {
            for (int z = 0; z < 1; ++z) {
                array_1[x][y][z] = 833;
            }
        }
    }

    array_2 = array_1;

    ASSERT_TRUE(array_1 == array_2);
}

TEST(ThreeDArraySuite, ReplacingValue) {
    ThreeDArray array_1 = ThreeDArray::make_array(22, 621, 8120);
    array_1[10][611][8100] = 3;

    array_1[10][611][8100] = 65056;

    ASSERT_EQ(array_1[10][611][8100], 65056);
}



