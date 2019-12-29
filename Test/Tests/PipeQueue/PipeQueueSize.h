#include "../ClassHeader.h"

TEST(PipeQueueTestSize, size_0)
{
    PLS::PipeQueue<int> pipe;
    
    ASSERT_NO_THROW(pipe.size());
    ASSERT_EQ(pipe.size(), 0);
}


TEST(PipeQueueTestSize, size_many)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3, 4};
    
    ASSERT_NO_THROW(pipe.size());
    ASSERT_EQ(pipe.size(), 4);
}


TEST(PipeQueueTestSize, size_pop_to_zero)
{
    PLS::PipeQueue<int> pipe;
    int buffer;

    pipe.push(1);
    ASSERT_EQ(pipe.size(), 1);

    pipe.try_pop(buffer);
    ASSERT_EQ(pipe.size(), 0);
}


TEST(PipeQueueTestSize, size_pop_to_less)
{
    PLS::PipeQueue<int> pipe = {1, 2};
    int buffer;

    ASSERT_EQ(pipe.size(), 2);

    pipe.try_pop(buffer);
    ASSERT_EQ(pipe.size(), 1);
}


TEST(PipeQueueTestSize, size_minus_zero)
{
    PLS::PipeQueue<int> pipe = {1};
    int buffer;

    ASSERT_EQ(pipe.size(), 1);

    pipe.try_pop(buffer);
    pipe.try_pop(buffer);

    ASSERT_EQ(pipe.size(), 0);
}