#include "../ClassHeader.h"

TEST(PipeQueueTestPush, push_empty)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(1));
}

TEST(PipeQueueTestPush, push_multiple)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.push(2));
    ASSERT_NO_THROW(pipe.push(3));
}

TEST(PipeQueueTestPush, push_deduct)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(5.5));
}

TEST(PipeQueueTestPush, push_after_pop)
{
    PLS::PipeQueue<int> pipe;
    int buffer;

    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_NO_THROW(pipe.push(1));
}


TEST(PipeQueueTestPush, push_correct_value)
{
    PLS::PipeQueue<int> pipe;
    int buffer;

    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.push(2));

    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(buffer, 1);

    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(buffer, 2);
}