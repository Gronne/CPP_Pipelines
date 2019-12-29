#include "../ClassHeader.h"


TEST(PipeQueueTestAssignmentEqualTo, equal_true_empty)
{
    PLS::PipeQueue<int> pipeA;
    PLS::PipeQueue<int> pipeB;

    ASSERT_NO_THROW(pipeA == pipeB);
    ASSERT_TRUE(pipeA == pipeB);
    ASSERT_TRUE(pipeB == pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, notEqual_false_empty)
{
    PLS::PipeQueue<int> pipeA;
    PLS::PipeQueue<int> pipeB;

    ASSERT_NO_THROW(pipeA != pipeB);
    ASSERT_FALSE(pipeA != pipeB);
    ASSERT_FALSE(pipeB != pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, equal_true_filled_sameSize)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA == pipeB);
    ASSERT_TRUE(pipeA == pipeB);
    ASSERT_TRUE(pipeB == pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, notEqual_false_filled_sameSize)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA != pipeB);
    ASSERT_FALSE(pipeA != pipeB);
    ASSERT_FALSE(pipeB != pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, equal_true_other_type_sameSize)
{
    PLS::PipeQueue<std::string> pipeA = {"Hello", "World"};
    PLS::PipeQueue<std::string> pipeB  = {"Hello", "World"};

    ASSERT_NO_THROW(pipeA == pipeB);
    ASSERT_TRUE(pipeA == pipeB);
    ASSERT_TRUE(pipeB == pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, notEqual_false_other_type_sameSize)
{
    PLS::PipeQueue<std::string> pipeA = {"Hello", "World"};
    PLS::PipeQueue<std::string> pipeB  = {"Hello", "World"};

    ASSERT_NO_THROW(pipeA != pipeB);
    ASSERT_FALSE(pipeA != pipeB);
    ASSERT_FALSE(pipeB != pipeA);
}


//-----Oppisite-----

TEST(PipeQueueTestAssignmentEqualTo, equal_false_filled_sameSize)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 4};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA == pipeB);
    ASSERT_FALSE(pipeA == pipeB);
    ASSERT_FALSE(pipeB == pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, notEqual_true_filled_sameSize)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 4};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA != pipeB);
    ASSERT_TRUE(pipeA != pipeB);
    ASSERT_TRUE(pipeB != pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, equal_false_other_type_sameSize)
{
    PLS::PipeQueue<std::string> pipeA = {"Hello", "World!"};
    PLS::PipeQueue<std::string> pipeB  = {"Hello", "World"};

    ASSERT_NO_THROW(pipeA == pipeB);
    ASSERT_FALSE(pipeA == pipeB);
    ASSERT_FALSE(pipeB == pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, notEqual_true_other_type_sameSize)
{
    PLS::PipeQueue<std::string> pipeA = {"Hello", "World!"};
    PLS::PipeQueue<std::string> pipeB  = {"Hello", "World"};

    ASSERT_NO_THROW(pipeA != pipeB);
    ASSERT_TRUE(pipeA != pipeB);
    ASSERT_TRUE(pipeB != pipeA);
}



//----DifferentSize----


TEST(PipeQueueTestAssignmentEqualTo, equal_false_filled_diffSize)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3, 4};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA == pipeB);
    ASSERT_FALSE(pipeA == pipeB);
    ASSERT_FALSE(pipeB == pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, notEqual_true_filled_diffSize)
{
    PLS::PipeQueue<int> pipeA = {1, 2, 3, 4};
    PLS::PipeQueue<int> pipeB = {1, 2, 3};

    ASSERT_NO_THROW(pipeA != pipeB);
    ASSERT_TRUE(pipeA != pipeB);
    ASSERT_TRUE(pipeB != pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, equal_false_other_type_diffSize)
{
    PLS::PipeQueue<std::string> pipeA = {"Hello", "World", "!"};
    PLS::PipeQueue<std::string> pipeB  = {"Hello", "World"};

    ASSERT_NO_THROW(pipeA == pipeB);
    ASSERT_FALSE(pipeA == pipeB);
    ASSERT_FALSE(pipeB == pipeA);
}


TEST(PipeQueueTestAssignmentEqualTo, notEqual_true_other_type_diffSize)
{
    PLS::PipeQueue<std::string> pipeA = {"Hello", "World!", "!"};
    PLS::PipeQueue<std::string> pipeB  = {"Hello", "World"};

    ASSERT_NO_THROW(pipeA != pipeB);
    ASSERT_TRUE(pipeA != pipeB);
    ASSERT_TRUE(pipeB != pipeA);
}