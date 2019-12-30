#include "../ClassHeader.h"

TEST(PipeQueueTestAssignmentMoveCopy, copy_noData_noData)
{
    PLS::PipeQueue<int> testQueue;
    PLS::PipeQueue<int> copyQueue;

    ASSERT_NO_THROW(testQueue = copyQueue);
}


TEST(PipeQueueTestAssignmentMoveCopy, copy_noData_data)
{
    PLS::PipeQueue<int> copyQueue = {1, 2, 3};
    PLS::PipeQueue<int> testQueue;

    ASSERT_NO_THROW(testQueue = copyQueue);

    ASSERT_TRUE(testQueue == copyQueue);

    int buffer;
    testQueue.try_pop(buffer);
    ASSERT_FALSE(testQueue == copyQueue);
}

TEST(PipeQueueTestAssignmentMoveCopy, copy_data_data)
{
    PLS::PipeQueue<int> testQueue = { 5, 6, 7, 8};
    PLS::PipeQueue<int> copyQueue = { 1, 2, 3};

    ASSERT_NO_THROW(testQueue = copyQueue);

    ASSERT_TRUE(testQueue == copyQueue);

    int buffer;
    testQueue.try_pop(buffer);
    ASSERT_FALSE(testQueue == copyQueue);
}


TEST(PipeQueueTestAssignmentMoveCopy, move_noData_noData)
{
    PLS::PipeQueue<int> testQueue;
    PLS::PipeQueue<int> moveQueue;

    ASSERT_NO_THROW(testQueue = std::move(moveQueue));
}


TEST(PipeQueueTestAssignmentMoveCopy, move_noData_data)
{
    PLS::PipeQueue<int> moveQueue = {1, 2, 3};
    PLS::PipeQueue<int> testQueue;

    ASSERT_NO_THROW(testQueue = std::move(moveQueue));

    ASSERT_EQ(testQueue.size(), 3);
    ASSERT_EQ(moveQueue.size(), 0);
}


TEST(PipeQueueTestAssignmentMoveCopy, move_data_data)
{
    PLS::PipeQueue<int> testQueue = {5, 6, 7, 8};
    PLS::PipeQueue<int> moveQueue = {1, 2, 3};

    ASSERT_NO_THROW(testQueue = std::move(moveQueue));

    ASSERT_EQ(testQueue.size(), 3);
    ASSERT_EQ(moveQueue.size(), 0);
}