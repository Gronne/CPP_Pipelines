#include "../ClassHeader.h"

TEST(PipeQueueTestBack, Back_push_empty)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(1));
}

TEST(PipeQueueTestBack, Back_push_multiple)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.push(2));
    ASSERT_NO_THROW(pipe.push(3));
}

TEST(PipeQueueTestBack, Back_push_deduct)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(5.5));
}

TEST(PipeQueueTestBack, Back_push_after_pop)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.pop());
    ASSERT_NO_THROW(pipe.push(1));
}