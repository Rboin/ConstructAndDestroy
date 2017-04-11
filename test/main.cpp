//
// Created by robin on 2/21/17.
//

#include <gtest/gtest.h>

/**
 * This function initializes our Google test environment.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}