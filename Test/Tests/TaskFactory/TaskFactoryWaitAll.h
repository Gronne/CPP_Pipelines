#include "../ClassHeader.h"



TEST(TaskFactoryTestWaitAll, wait_one_tasks)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn, pipeOut;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut));

    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f));
}


TEST(TaskFactoryTestWaitAll, wait_multiple_tasks)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn, pipeOut;

    std::future<void> f1, f2, f3;

    ASSERT_NO_THROW(f1 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut));
    ASSERT_NO_THROW(f2 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut));
    ASSERT_NO_THROW(f3 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut));

    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f1, f2, f3));
}


TEST(TaskFactoryTestWaitAll, wait_different_tasks)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn, pipeOut;

    std::future<void> fPipe;

    std::promise<double> p;
    std::future<double> fOther = p.get_future();

    ASSERT_NO_THROW(fPipe  = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut));
    ASSERT_NO_THROW(std::thread([](std::promise<double> &&promise) { promise.set_value_at_thread_exit(1); }, std::move(p)).detach());

    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(fPipe, fOther));
}