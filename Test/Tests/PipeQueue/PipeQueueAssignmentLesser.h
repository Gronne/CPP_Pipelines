#include "../ClassHeader.h"


TEST(PipeQueueTestAssignmentLesser, lesser_true_lesser)
{
    PLS::PipeQueue<int> pipeA = {1, 2};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA < pipeB);
    ASSERT_TRUE(pipeA < pipeB);
}


TEST(PipeQueueTestAssignmentLesser, lesser_true_lesser_one_empty)
{
    PLS::PipeQueue<int> pipeA;;
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA < pipeB);
    ASSERT_TRUE(pipeA < pipeB);
}


TEST(PipeQueueTestAssignmentLesser, lesser_false_larger)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3, 4};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA < pipeB);
    ASSERT_FALSE(pipeA < pipeB);
}


TEST(PipeQueueTestAssignmentLesser, lesser_false_larger_one_empty)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3, 4};
    PLS::PipeQueue<int> pipeB;

    ASSERT_NO_THROW(pipeA < pipeB);
    ASSERT_FALSE(pipeA < pipeB);
}


TEST(PipeQueueTestAssignmentLesser, lesser_false_equal_empty)
{
    PLS::PipeQueue<int> pipeA;
    PLS::PipeQueue<int> pipeB;

    ASSERT_NO_THROW(pipeA < pipeB);
    ASSERT_FALSE(pipeA < pipeB);
}


TEST(PipeQueueTestAssignmentLesser, lesser_false_equal_filled)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA < pipeB);
    ASSERT_FALSE(pipeA < pipeB);
}

