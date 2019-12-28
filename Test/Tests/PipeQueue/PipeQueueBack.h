#include "../ClassHeader.h"

TEST(PipeQueueTestBack, Back_push_empty)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push_back(1));
}

TEST(PipeQueueTestBack, Back_push_multiple)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push_back(1));
    ASSERT_NO_THROW(pipe.push_back(2));
    ASSERT_NO_THROW(pipe.push_back(3));
}

TEST(PipeQueueTestBack, Back_push_deduct)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push_back(5.5));
}

TEST(PipeQueueTestBack, Back_push_after_pop)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push_back(1));
    ASSERT_NO_THROW(pipe.push_back(1));
    ASSERT_NO_THROW(pipe.pop_front());
    ASSERT_NO_THROW(pipe.push_back(1));
}