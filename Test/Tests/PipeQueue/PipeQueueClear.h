#include "../ClassHeader.h"


TEST(PipeQueueTestClear, clear_empty)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.clear());
    ASSERT_TRUE(pipe.empty());
}


TEST(PipeQueueTestClear, clear_filled)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};

    ASSERT_NO_THROW(pipe.clear());
    ASSERT_TRUE(pipe.empty());
}


TEST(PipeQueueTestClear, clear_push_afterward)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.clear());
    ASSERT_TRUE(pipe.empty());

    pipe.push(5);

    ASSERT_FALSE(pipe.empty());
}