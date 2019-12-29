#include "../ClassHeader.h"

TEST(PipeQueueTestSize, size_0)
{
    PLS::PipeQueue<int> pipe;
    
    ASSERT_NO_THROW(pipe.size());
    ASSERT_EQ(pipe.size(), 0);
}


TEST(PipeQueueTestSize, size_many)
{
    PLS::PipeQueue<int> pipe;
    pipe.push(1);
    pipe.push(1);
    pipe.push(1);
    pipe.push(1);
    
    ASSERT_NO_THROW(pipe.size());
    ASSERT_EQ(pipe.size(), 4);
}


TEST(PipeQueueTestSize, size_pop_to_zero)
{
    PLS::PipeQueue<int> pipe;

    pipe.push(1);
    ASSERT_EQ(pipe.size(), 1);

    pipe.pop();
    ASSERT_EQ(pipe.size(), 0);
}


TEST(PipeQueueTestSize, size_pop_to_less)
{
    PLS::PipeQueue<int> pipe;

    pipe.push(1);
    pipe.push(1);
    ASSERT_EQ(pipe.size(), 2);

    pipe.pop();
    ASSERT_EQ(pipe.size(), 1);
}


TEST(PipeQueueTestSize, size_minus_zero)
{
    PLS::PipeQueue<int> pipe;

    pipe.push(1);
    ASSERT_EQ(pipe.size(), 1);

    pipe.pop();
    ASSERT_THROW(pipe.pop(), std::exception);

    ASSERT_EQ(pipe.size(), 0);
}