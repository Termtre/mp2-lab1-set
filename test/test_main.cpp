#include <gtest.h>
#include <iostream>
int main(int argc, char **argv) {
    int a;
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    std::cin >> a;
    return 1;
}
