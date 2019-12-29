#include "../ClassHeader.h"

TEST(PipeQueueTestEmpty, empty_false)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};

    ASSERT_NO_THROW(pipe.empty());
    ASSERT_FALSE(pipe.empty());
}


TEST(PipeQueueTestEmpty, empty_true)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.empty());
    ASSERT_TRUE(pipe.empty());
}


TEST(PipeQueueTestEmpty, empty_true_to_false)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.empty());
    ASSERT_TRUE(pipe.empty());

    pipe.push(5);
    ASSERT_FALSE(pipe.empty());
}


TEST(PipeQueueTestEmpty, empty_false_to_true)
{
    PLS::PipeQueue<int> pipe = {1};

    ASSERT_NO_THROW(pipe.empty());
    ASSERT_FALSE(pipe.empty());

    int buffer;
    pipe.try_pop(buffer);
    ASSERT_TRUE(pipe.empty());
}


TEST(PipeQueueTestEmpty, empty_clear)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};

    ASSERT_NO_THROW(pipe.empty());
    ASSERT_FALSE(pipe.empty());

    pipe.clear();
    ASSERT_TRUE(pipe.empty());
}