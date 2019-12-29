#include "../ClassHeader.h"

TEST(PipeQueueTestFront, Front_pop_empty)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_THROW(pipe.pop(), std::exception);
}

TEST(PipeQueueTestFront, Front_pop_to_empty)
{
    PLS::PipeQueue<int> pipe;

    pipe.push(1);

    ASSERT_NO_THROW(pipe.pop());
}

TEST(PipeQueueTestFront, Front_pop_to_less)
{
    PLS::PipeQueue<int> pipe;

    pipe.push(1);
    pipe.push(2);

    ASSERT_NO_THROW(pipe.pop());
}

TEST(PipeQueueTestFront, Front_pop_right_element)
{
    PLS::PipeQueue<int> pipe;

    pipe.push(1);
    pipe.push(2);

    ASSERT_NO_THROW(pipe.pop());

    ASSERT_EQ(pipe.front(), 2);
}


TEST(PipeQueueTestFront, Front_pop_multiple)
{
    PLS::PipeQueue<int> pipe;

    pipe.push(1);
    pipe.push(2);

    ASSERT_NO_THROW(pipe.pop());
    ASSERT_NO_THROW(pipe.pop());
}



TEST(PipeQueueTestFront, Front_look_empty)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_THROW(pipe.front(), std::exception);
}

TEST(PipeQueueTestFront, Front_look_one_element)
{
    PLS::PipeQueue<int> pipe;
    pipe.push(1);

    ASSERT_NO_THROW(pipe.front());
    ASSERT_EQ(pipe.front(), 1);
}

TEST(PipeQueueTestFront, Front_look_many_element)
{
    PLS::PipeQueue<int> pipe;
    pipe.push(1);
    pipe.push(1);
    pipe.push(1);
    pipe.push(1);

    ASSERT_NO_THROW(pipe.front());
}

TEST(PipeQueueTestFront, Front_look_after_pop)
{
    PLS::PipeQueue<int> pipe;
    pipe.push(1);
    pipe.push(1);
    pipe.pop();

    ASSERT_NO_THROW(pipe.front());
}

TEST(PipeQueueTestFront, Front_look_many_looks)
{
    PLS::PipeQueue<int> pipe;
    pipe.push(1);
    pipe.push(1);

    ASSERT_NO_THROW(pipe.front());
    ASSERT_NO_THROW(pipe.front());
    ASSERT_NO_THROW(pipe.front());
    ASSERT_NO_THROW(pipe.front());
}


TEST(PipeQueueTestFront, Front_look_no_remove)
{
    PLS::PipeQueue<int> pipe;
    pipe.push(1);
    pipe.push(1);

    ASSERT_NO_THROW(pipe.front());
    ASSERT_NO_THROW(pipe.front());

    ASSERT_EQ(pipe.size(), 2);
}


