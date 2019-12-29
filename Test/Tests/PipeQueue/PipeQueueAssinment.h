#include "../ClassHeader.h"

TEST(PipeQueueTestAssignment, assignment_copy_noData_noData)
{
    PLS::PipeQueue<int> testQueue;
    PLS::PipeQueue<int> copyQueue;

    ASSERT_NO_THROW(testQueue = copyQueue);
}


TEST(PipeQueueTestAssignment, assignment_copy_noData_data)
{
    PLS::PipeQueue<int> testQueue;
    PLS::PipeQueue<int> copyQueue;      
    copyQueue.push(1);
    copyQueue.push(2);
    copyQueue.push(3);

    ASSERT_NO_THROW(testQueue = copyQueue);

    ASSERT_EQ(testQueue.size(), copyQueue.size());

    testQueue.pop();
    ASSERT_NE(testQueue.size(), copyQueue.size());
}

TEST(PipeQueueTestAssignment, assignment_copy_data_data)
{
    PLS::PipeQueue<int> testQueue;
    testQueue.push(5);
    testQueue.push(6);
    testQueue.push(7);
    testQueue.push(8);


    PLS::PipeQueue<int> copyQueue;      
    copyQueue.push(1);
    copyQueue.push(2);
    copyQueue.push(3);

    ASSERT_NO_THROW(testQueue = copyQueue);

    ASSERT_EQ(testQueue.size(), copyQueue.size());

    testQueue.pop();
    ASSERT_NE(testQueue.size(), copyQueue.size());
}


TEST(PipeQueueTestAssignment, assignment_move_noData_noData)
{
    PLS::PipeQueue<int> testQueue;
    PLS::PipeQueue<int> moveQueue;

    ASSERT_NO_THROW(testQueue = std::move(moveQueue));
}


TEST(PipeQueueTestAssignment, assignment_move_noData_data)
{
    PLS::PipeQueue<int> testQueue;
    PLS::PipeQueue<int> moveQueue;      
    moveQueue.push(1);
    moveQueue.push(2);
    moveQueue.push(3);

    ASSERT_NO_THROW(testQueue = std::move(moveQueue));

    ASSERT_EQ(testQueue.size(), 3);
    ASSERT_EQ(moveQueue.size(), 0);
}

TEST(PipeQueueTestAssignment, assignment_move_data_data)
{
    PLS::PipeQueue<int> testQueue;
    testQueue.push(5);
    testQueue.push(6);
    testQueue.push(7);
    testQueue.push(8);


    PLS::PipeQueue<int> moveQueue;      
    moveQueue.push(1);
    moveQueue.push(2);
    moveQueue.push(3);

    ASSERT_NO_THROW(testQueue = std::move(moveQueue));

    ASSERT_EQ(testQueue.size(), 3);
    ASSERT_EQ(moveQueue.size(), 0);
}