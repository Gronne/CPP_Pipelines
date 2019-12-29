#include "../ClassHeader.h"


//------in------

TEST(PipeQueueTestAssignmentInOut, in_empty)
{
    PLS::PipeQueue<int> pipeA;
    PLS::PipeQueue<int> pipeB;

    int buffer = 1;

    ASSERT_NO_THROW(pipeA >> buffer);
    ASSERT_FALSE(pipeB >> buffer);

    ASSERT_EQ(buffer, 1);
}


TEST(PipeQueueTestAssignmentInOut, in_one_element)
{
    PLS::PipeQueue<int> pipeA = {1};
    PLS::PipeQueue<int> pipeB = {1};

    int buffer;

    ASSERT_NO_THROW(pipeA >> buffer);
    ASSERT_TRUE(pipeB >> buffer);
    ASSERT_EQ(buffer, 1);

    ASSERT_FALSE(pipeA >> buffer);
    ASSERT_EQ(buffer, 1);
}


TEST(PipeQueueTestAssignmentInOut, in_many_element)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3, 4};
    PLS::PipeQueue<int> pipeB = {1, 2, 3, 4};

    int buffer;

    ASSERT_NO_THROW(pipeA >> buffer);
    ASSERT_TRUE(pipeB >> buffer);
    ASSERT_EQ(buffer, 1);

    pipeA >> buffer;
    ASSERT_EQ(buffer, 2);
    ASSERT_TRUE(pipeB >> buffer);

    pipeA >> buffer;
    ASSERT_EQ(buffer, 3);
    ASSERT_TRUE(pipeB >> buffer);

    pipeA >> buffer;
    ASSERT_EQ(buffer, 4);
    ASSERT_TRUE(pipeB >> buffer);

    pipeA >> buffer;
    ASSERT_EQ(buffer, 4);
    ASSERT_FALSE(pipeB >> buffer);
}


//------out copy-------
TEST(PipeQueueTestAssignmentInOut, out_copy_empty_one)
{
    PLS::PipeQueue<int> pipeA;

    int buffer = 1;

    ASSERT_NO_THROW(pipeA << buffer);

    int check;
    pipeA >> check;

    ASSERT_EQ(buffer, check);
}


TEST(PipeQueueTestAssignmentInOut, out_copy_empty_many)
{
    PLS::PipeQueue<int> pipeA;

    int buffer1 = 1;
    int buffer2 = 2;
    int buffer3 = 3;

    ASSERT_NO_THROW(pipeA << buffer1 << buffer2 << buffer3);

    int check;

    pipeA >> check;
    ASSERT_EQ(buffer1, check);

    pipeA >> check;
    ASSERT_EQ(buffer2, check);

    pipeA >> check;
    ASSERT_EQ(buffer3, check);
}


TEST(PipeQueueTestAssignmentInOut, out_copy_filled_one)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};

    int buffer = 1;

    ASSERT_NO_THROW(pipeA << buffer);

    int check;

    pipeA >> check;
    ASSERT_EQ(1, check);

    pipeA >> check;
    ASSERT_EQ(2, check);

    pipeA >> check;
    ASSERT_EQ(3, check);

    pipeA >> check;
    ASSERT_EQ(buffer, check);
}


TEST(PipeQueueTestAssignmentInOut, out_copy_filled_many)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};

    int buffer1 = 1;
    int buffer2 = 2;
    int buffer3 = 3;

    ASSERT_NO_THROW(pipeA << buffer1 << buffer2 << buffer3);

    int check;

    pipeA >> check;
    ASSERT_EQ(1, check);

    pipeA >> check;
    ASSERT_EQ(2, check);

    pipeA >> check;
    ASSERT_EQ(3, check);

    pipeA >> check;
    ASSERT_EQ(buffer1, check);

    pipeA >> check;
    ASSERT_EQ(buffer2, check);

    pipeA >> check;
    ASSERT_EQ(buffer3, check);
}

//------out move-------

TEST(PipeQueueTestAssignmentInOut, out_move_empty_one)
{
    PLS::PipeQueue<int> pipeA;

    ASSERT_NO_THROW(pipeA << 1);

    int check;
    pipeA >> check;

    ASSERT_EQ(1, check);
}


TEST(PipeQueueTestAssignmentInOut, out_move_empty_many)
{
    PLS::PipeQueue<int> pipeA;

    ASSERT_NO_THROW(pipeA << 1 << 2 << 3);

    int check;

    pipeA >> check;
    ASSERT_EQ(1, check);

    pipeA >> check;
    ASSERT_EQ(2, check);

    pipeA >> check;
    ASSERT_EQ(3, check);
}


TEST(PipeQueueTestAssignmentInOut, out_move_filled_one)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};

    ASSERT_NO_THROW(pipeA << 1);

    int check;

    pipeA >> check;
    ASSERT_EQ(1, check);

    pipeA >> check;
    ASSERT_EQ(2, check);

    pipeA >> check;
    ASSERT_EQ(3, check);

    pipeA >> check;
    ASSERT_EQ(1, check);
}


TEST(PipeQueueTestAssignmentInOut, out_move_filled_many)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};

    ASSERT_NO_THROW(pipeA << 1 << 2 << 3);

    int check;

    pipeA >> check;
    ASSERT_EQ(1, check);

    pipeA >> check;
    ASSERT_EQ(2, check);

    pipeA >> check;
    ASSERT_EQ(3, check);

    pipeA >> check;
    ASSERT_EQ(1, check);

    pipeA >> check;
    ASSERT_EQ(2, check);

    pipeA >> check;
    ASSERT_EQ(3, check);
}