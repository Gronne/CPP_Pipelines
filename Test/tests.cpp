#include "../Pipelines/include/PipeQueue.hpp"
#include <gtest/gtest.h>


TEST(PipeQueueTestInit, push)
{
    PLS::PipeQueue<std::string> testQueue;
    testQueue.push_back("Hello");
    testQueue.push_back(", world!");

    ASSERT_EQ(testQueue.front(), "Hello");
    testQueue.pop_front();

    ASSERT_EQ(testQueue.front(), ", world!");
    testQueue.pop_front();
}









int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}