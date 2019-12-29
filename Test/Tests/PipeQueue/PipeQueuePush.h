#include "../ClassHeader.h"

TEST(PipeQueueTestPush, push_empty_rValue)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(1));
}


TEST(PipeQueueTestPush, push_empty_lValue)
{
    PLS::PipeQueue<int> pipe;

    int lValue = 1;
    ASSERT_NO_THROW(pipe.push(lValue));
}


TEST(PipeQueueTestPush, push_multiple_rValue)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.push(2));
    ASSERT_NO_THROW(pipe.push(3));
}


TEST(PipeQueueTestPush, push_multiple_lValue)
{
    PLS::PipeQueue<int> pipe;

    int lValue1 = 1;
    int lValue2 = 2;
    int lValue3 = 3;

    ASSERT_NO_THROW(pipe.push(lValue1));
    ASSERT_NO_THROW(pipe.push(lValue2));
    ASSERT_NO_THROW(pipe.push(lValue3));
}


TEST(PipeQueueTestPush, push_deduct_rValue)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.push(5.5));
}


TEST(PipeQueueTestPush, push_deduct_lValue)
{
    PLS::PipeQueue<int> pipe;

    double lValue = 5.5;

    ASSERT_NO_THROW(pipe.push(lValue));
}


TEST(PipeQueueTestPush, push_after_pop_rValue)
{
    PLS::PipeQueue<int> pipe;
    int buffer;

    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.push(1));
    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_NO_THROW(pipe.push(1));
}


TEST(PipeQueueTestPush, push_after_pop_lValue)
{
    PLS::PipeQueue<int> pipe;
    int buffer;

    int lValue = 1;

    ASSERT_NO_THROW(pipe.push(lValue));
    ASSERT_NO_THROW(pipe.push(lValue));
    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_NO_THROW(pipe.push(lValue));
}


TEST(PipeQueueTestPush, push_correct_value_rValue)
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


TEST(PipeQueueTestPush, push_correct_value_lValue)
{
    PLS::PipeQueue<int> pipe;
    int buffer;

    int lValue1 = 1;
    int lValue2 = 2;

    ASSERT_NO_THROW(pipe.push(lValue1));
    ASSERT_NO_THROW(pipe.push(lValue2));

    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(buffer, lValue1);

    ASSERT_NO_THROW(pipe.try_pop(buffer));
    ASSERT_EQ(buffer, lValue2);
}