#include "../ClassHeader.h"

TEST(PipeQueueTestFront, Front)
{
    PLS::PipeQueue<std::string> testQueue;
    testQueue.push_back("Hello");
    testQueue.push_back(", world!");

    ASSERT_EQ(testQueue.front(), "Hello");
    testQueue.pop_front();

    ASSERT_EQ(testQueue.front(), ", world!");
    testQueue.pop_front();
}