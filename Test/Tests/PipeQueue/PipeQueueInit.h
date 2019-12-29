#include "../ClassHeader.h"

TEST(PipeQueueTestInit, init_container_default)
{
    ASSERT_NO_THROW(PLS::PipeQueue<std::string> testQueue);
}


TEST(PipeQueueTestInit, init_container_custom)
{
    typedef std::string T;
    typedef PLS::PipeQueue<T, std::vector<T>> PS;   //typedef instead of using, no new templating is needed

    ASSERT_NO_THROW(PS testQueue);
}


TEST(PipeQueueTestInit, init_type_int)
{
    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue);
}


TEST(PipeQueueTestInit, init_type_string)
{
    ASSERT_NO_THROW(PLS::PipeQueue<std::string> testQueue);
}


TEST(PipeQueueTestInit, init_type_custom)
{
    struct CustomType { };

    ASSERT_NO_THROW(PLS::PipeQueue<CustomType> testQueue);
}


TEST(PipeQueueTestInit, init_copy_no_data)
{
    PLS::PipeQueue<int> copyQueue;
    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue(copyQueue));
}


TEST(PipeQueueTestInit, init_copy_data)
{
    PLS::PipeQueue<int> copyQueue = {1, 2, 3};

    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue(copyQueue));
    PLS::PipeQueue<int> testQueue2(copyQueue);

    ASSERT_TRUE(testQueue2 == copyQueue);

    int buffer;
    testQueue2.try_pop(buffer);
    ASSERT_FALSE(testQueue2 == copyQueue);
}


TEST(PipeQueueTestInit, init_move_no_data)
{
    PLS::PipeQueue<int> moveQueue;
    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue(std::move(moveQueue)));
}


TEST(PipeQueueTestInit, init_move_data_no_error)
{
    PLS::PipeQueue<int> moveQueue = {1, 2, 3};

    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue(std::move(moveQueue)));
}


TEST(PipeQueueTestInit, init_move_data_correct)
{
    PLS::PipeQueue<int> moveQueue = {1, 2, 3};

    PLS::PipeQueue<int> testQueue(std::move(moveQueue));

    ASSERT_EQ(testQueue.size(), 3);
    ASSERT_EQ(moveQueue.size(), 0);
}


TEST(PipeQueueTestInit, init_initializeList_one) 
{
    PLS::PipeQueue<int> pipe = {1};

    ASSERT_EQ(pipe.size(), 1);

    int buffer;
    pipe.try_pop(buffer);

    ASSERT_EQ(buffer, 1);
}


TEST(PipeQueueTestInit, init_initializeList_many) 
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};

    ASSERT_EQ(pipe.size(), 3);

    int buffer;

    pipe.try_pop(buffer);
    ASSERT_EQ(buffer, 1);

    pipe.try_pop(buffer);
    ASSERT_EQ(buffer, 2);

    pipe.try_pop(buffer);
    ASSERT_EQ(buffer, 3);
}


