#include "../ClassHeader.h"

TEST(PipeQueueTestPop, pop_empty)
{
    PLS::PipeQueue<int> pipe;

    int buffer;
    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_FALSE(pipe.try_pop(buffer));
}


TEST(PipeQueueTestPop, pop_to_empty)
{
    PLS::PipeQueue<int> pipe1 = {1};
    PLS::PipeQueue<int> pipe2 = {1};

    int buffer;
    ASSERT_NO_THROW(pipe1.try_pop(buffer));
    ASSERT_TRUE(pipe2.try_pop(buffer));
    ASSERT_EQ(buffer, 1);
}


TEST(PipeQueueTestPop, pop_to_less)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};

    int buffer;
    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_TRUE(pipe.try_pop(buffer));
}


TEST(PipeQueueTestPop, pop_right_element)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};

    ASSERT_EQ(pipe.size(), 3);

    int buffer;
    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(pipe.size(), 2);
}


TEST(PipeQueueTestPop, pop_multiple)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};

    int buffer;
    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(buffer, 1);

    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(buffer, 2);

    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(buffer, 3);

    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(buffer, 3);
}




