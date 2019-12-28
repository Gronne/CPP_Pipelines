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
    copyQueue.push_back(1);
    copyQueue.push_back(2);
    copyQueue.push_back(3);

    ASSERT_NO_THROW(testQueue = copyQueue);

    ASSERT_EQ(testQueue.size(), copyQueue.size());

    testQueue.pop_front();
    ASSERT_NE(testQueue.size(), copyQueue.size());
}

TEST(PipeQueueTestAssignment, assignment_copy_data_data)
{
    PLS::PipeQueue<int> testQueue;
    testQueue.push_back(5);
    testQueue.push_back(6);
    testQueue.push_back(7);
    testQueue.push_back(8);


    PLS::PipeQueue<int> copyQueue;      
    copyQueue.push_back(1);
    copyQueue.push_back(2);
    copyQueue.push_back(3);

    ASSERT_NO_THROW(testQueue = copyQueue);

    ASSERT_EQ(testQueue.size(), copyQueue.size());

    testQueue.pop_front();
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
    moveQueue.push_back(1);
    moveQueue.push_back(2);
    moveQueue.push_back(3);

    ASSERT_NO_THROW(testQueue = std::move(moveQueue));

    ASSERT_EQ(testQueue.size(), 3);
    ASSERT_EQ(moveQueue.size(), 0);
}

TEST(PipeQueueTestAssignment, assignment_move_data_data)
{
    PLS::PipeQueue<int> testQueue;
    testQueue.push_back(5);
    testQueue.push_back(6);
    testQueue.push_back(7);
    testQueue.push_back(8);


    PLS::PipeQueue<int> moveQueue;      
    moveQueue.push_back(1);
    moveQueue.push_back(2);
    moveQueue.push_back(3);

    ASSERT_NO_THROW(testQueue = std::move(moveQueue));

    ASSERT_EQ(testQueue.size(), 3);
    ASSERT_EQ(moveQueue.size(), 0);
}