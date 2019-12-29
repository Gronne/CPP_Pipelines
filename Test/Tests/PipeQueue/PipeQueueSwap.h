#include "../ClassHeader.h"

TEST(PipeQueueTestSwap, swap_empty)
{
    PLS::PipeQueue<int> pipeA;
    PLS::PipeQueue<int> pipeACopy(pipeA);
    PLS::PipeQueue<int> pipeB;
    PLS::PipeQueue<int> pipeBCopy(pipeB);

    ASSERT_NO_THROW(pipeA.swap(pipeB));

    ASSERT_TRUE(pipeA == pipeBCopy);
    ASSERT_TRUE(pipeB == pipeACopy);

}


TEST(PipeQueueTestSwap, swap_filled_same_size)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};
    PLS::PipeQueue<int> pipeACopy(pipeA);
    PLS::PipeQueue<int> pipeB = {4, 5, 6};
    PLS::PipeQueue<int> pipeBCopy(pipeB);

    ASSERT_NO_THROW(pipeA.swap(pipeB));

    ASSERT_TRUE(pipeA == pipeBCopy);
    ASSERT_TRUE(pipeB == pipeACopy);
}


TEST(PipeQueueTestSwap, swap_filled_diff_size_to)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};
    PLS::PipeQueue<int> pipeACopy(pipeA);
    PLS::PipeQueue<int> pipeB = {1, 2, 3, 4, 5, 6};
    PLS::PipeQueue<int> pipeBCopy(pipeB);

    ASSERT_NO_THROW(pipeA.swap(pipeB));

    ASSERT_TRUE(pipeA == pipeBCopy);
    ASSERT_TRUE(pipeB == pipeACopy);
}


TEST(PipeQueueTestSwap, swap_filled_diff_size_from)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3, 4, 5, 6};
    PLS::PipeQueue<int> pipeACopy(pipeA);
    PLS::PipeQueue<int> pipeB = {1, 2, 3};
    PLS::PipeQueue<int> pipeBCopy(pipeB);

    ASSERT_NO_THROW(pipeA.swap(pipeB));

    ASSERT_TRUE(pipeA == pipeBCopy);
    ASSERT_TRUE(pipeB == pipeACopy);
}


TEST(PipeQueueTestSwap, swap_empty_and_filled)
{
    PLS::PipeQueue<int> pipeA;
    PLS::PipeQueue<int> pipeACopy(pipeA);
    PLS::PipeQueue<int> pipeB = {1, 2, 3, 4};
    PLS::PipeQueue<int> pipeBCopy(pipeB);

    ASSERT_NO_THROW(pipeA.swap(pipeB));

    ASSERT_TRUE(pipeA == pipeBCopy);
    ASSERT_TRUE(pipeB == pipeACopy);
}


TEST(PipeQueueTestSwap, swap_filled_and_empty)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3, 4};
    PLS::PipeQueue<int> pipeACopy(pipeA);
    PLS::PipeQueue<int> pipeB;
    PLS::PipeQueue<int> pipeBCopy(pipeB);

    ASSERT_NO_THROW(pipeA.swap(pipeB));

    ASSERT_TRUE(pipeA == pipeBCopy);
    ASSERT_TRUE(pipeB == pipeACopy);
}