#include "../ClassHeader.h"

TEST(PipeQueueTestInit, init_default)
{
    ASSERT_NO_THROW(PLS::PipeQueue<std::string> testQueue);
}


TEST(PipeQueueTestInit, init_FILO_queue)
{
    typedef std::string S;
    typedef PLS::PipeQueue<S, std::vector<S>> PS;

    ASSERT_NO_THROW(PS testQueue);
}


TEST(PipeQueueTestInit, init_FILO_queue_error)
{
    typedef std::string S;
    typedef PLS::PipeQueue<S, std::vector<int>> PS;

    ASSERT_THROW(PS testQueue, std::exception);
}
