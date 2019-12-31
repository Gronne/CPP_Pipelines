#include "../ClassHeader.h"


TEST(TaskFactoryTeststart_async_task, async_lambda_zeroIn_zeroOut)
{
    decltype(auto) lambdaFunction = []() 
        { 
            std::chrono::milliseconds(10); 
        };

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_oneIn_zeroOut)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_manyIn_zeroOut)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &inA, PLS::PipeQueue<int> &inB) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn1, pipeIn2;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn1, pipeIn2));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_zeroIn_oneOut)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &out) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeOut;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeOut));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_zeroIn_manyOut)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &outA, PLS::PipeQueue<int> &outB) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeOut1, pipeOut2;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeOut1, pipeOut2));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_oneIn_oneOut)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn, pipeOut;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_manyIn_oneOut)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &inA, PLS::PipeQueue<int> &inB, PLS::PipeQueue<int> &out) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn1, pipeIn2, pipeOut;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn1, pipeIn2, pipeOut));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_oneIn_manyOut)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &outA, PLS::PipeQueue<int> &outB) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn, pipeOut1, pipeOut2;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut1, pipeOut2));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_manyIn_manyOut)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &inA, PLS::PipeQueue<int> &inB, PLS::PipeQueue<int> &outA, PLS::PipeQueue<int> &outB) 
        { 
            std::chrono::milliseconds(10); 
        };

    PLS::PipeQueue<int> pipeIn1, pipeIn2, pipeOut1, pipeOut2;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn1, pipeIn2, pipeOut1, pipeOut2));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_oneExtraParam)
{
    decltype(auto) lambdaFunction = [](int, PLS::PipeQueue<int> &in) 
        {

        };

    PLS::PipeQueue<int> pipeIn;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, 42, pipeIn));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_lambda_manyExtraParam)
{
    decltype(auto) lambdaFunction = [](int i, std::string &s, PLS::PipeQueue<int> &in) 
        {
            
        };

    PLS::PipeQueue<int> pipeIn;

    std::string s = "Hello";

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, 42, s, pipeIn));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_different_type_pipes)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &A, PLS::PipeQueue<std::string> &B) {};

    PLS::PipeQueue<int> pipeA;
    PLS::PipeQueue<std::string> pipeB;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeA, pipeB));

    PLS::TaskFactory::wait_all(f);
}


TEST(TaskFactoryTeststart_async_task, async_different_container_pipes)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &A, PLS::PipeQueue<int, std::vector<int>> &B) {};

    PLS::PipeQueue<int> pipeA;
    PLS::PipeQueue<int, std::vector<int>> pipeB;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeA, pipeB));

    PLS::TaskFactory::wait_all(f);
}
