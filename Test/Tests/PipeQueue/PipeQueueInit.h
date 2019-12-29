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
    struct CustomType {
        
    };

    ASSERT_NO_THROW(PLS::PipeQueue<CustomType> testQueue);
}


TEST(PipeQueueTestInit, init_copy_no_data)
{
    PLS::PipeQueue<int> copyQueue;
    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue(copyQueue));
}


TEST(PipeQueueTestInit, init_copy_data)
{
    PLS::PipeQueue<int> copyQueue;      //Remember to test a different type in push
    copyQueue.push(1);
    copyQueue.push(2);
    copyQueue.push(3);

    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue(copyQueue));

    PLS::PipeQueue<int> testQueue2(copyQueue);

    ASSERT_EQ(testQueue2.size(), copyQueue.size());

    testQueue2.pop();
    ASSERT_NE(testQueue2.size(), copyQueue.size());
}


TEST(PipeQueueTestInit, init_move_no_data)
{
    PLS::PipeQueue<int> moveQueue;
    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue(std::move(moveQueue)));
}


TEST(PipeQueueTestInit, init_move_data_no_error)
{
    PLS::PipeQueue<int> moveQueue;      
    moveQueue.push(1);
    moveQueue.push(2);
    moveQueue.push(3);

    ASSERT_NO_THROW(PLS::PipeQueue<int> testQueue(std::move(moveQueue)));
}


TEST(PipeQueueTestInit, init_move_data_correct)
{
    PLS::PipeQueue<int> moveQueue;      
    moveQueue.push(1);
    moveQueue.push(2);
    moveQueue.push(3);

    PLS::PipeQueue<int> testQueue(std::move(moveQueue));

    ASSERT_EQ(testQueue.size(), 3);
    ASSERT_EQ(moveQueue.size(), 0);
}


