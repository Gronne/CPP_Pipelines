#include "../ClassHeader.h"


TEST(TaskFactoryTestFlow, flow_one_task)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            while(!in.eof())
                ASSERT_NO_THROW(out.push(in.pop()));
            
            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn, pipeOut;

    pipeIn.push(1);
    pipeIn.push(2);
    pipeIn.push(3);

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f));


    ASSERT_EQ(pipeOut.size(), 3);       //== will make this easier
    ASSERT_EQ(pipeOut.pop(), 1);
    ASSERT_EQ(pipeOut.pop(), 2);
    ASSERT_EQ(pipeOut.pop(), 3);
}


TEST(TaskFactoryTestFlow, flow_two_tasks)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            while(!in.eof())
                ASSERT_NO_THROW(out.push(in.pop()));
            
            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn, pipeOut1, pipeOut2;

    pipeIn.push(1);
    pipeIn.push(2);
    pipeIn.push(3);

    std::future<void> f1;
    std::future<void> f2;

    ASSERT_NO_THROW(f1 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut1));
    ASSERT_NO_THROW(f2 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeOut1, pipeOut2));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f1, f2));

    ASSERT_EQ(pipeOut2.size(), 3);       //== will make this easier
    ASSERT_EQ(pipeOut2.pop(), 1);
    ASSERT_EQ(pipeOut2.pop(), 2);
    ASSERT_EQ(pipeOut2.pop(), 3);
}


TEST(TaskFactoryTestFlow, flow_two_tasks_one_inputPipe)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            while(!in.eof())
                ASSERT_NO_THROW(out.push(in.pop()));
            
            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn, pipeOut1, pipeOut2;

    pipeIn.push(1);
    pipeIn.push(2);
    pipeIn.push(3);
    pipeIn.push(4);

    std::future<void> f1;
    std::future<void> f2;

    ASSERT_NO_THROW(f1 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut1));
    ASSERT_NO_THROW(f2 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut2));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f1, f2));

    ASSERT_EQ(pipeOut1.size() + pipeOut2.size(), 4);
    ASSERT_EQ(pipeIn.size(), 0);
}


TEST(TaskFactoryTestFlow, flow_one_tasks_two_pipes)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &outA, PLS::PipeQueue<int> &outB) 
        { 
            int buffer;
            while(!in.eof())
            {
                buffer = in.pop();
                ASSERT_NO_THROW(outA.push(buffer));
                ASSERT_NO_THROW(outB.push(buffer));
            }
            
            outA.set_eof();
            outB.set_eof();
        };

    PLS::PipeQueue<int> pipeIn, pipeOut1, pipeOut2;

    pipeIn.push(1);
    pipeIn.push(2);
    pipeIn.push(3);

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut1, pipeOut2));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f));

    ASSERT_EQ(pipeOut1.size(), 3);  
    ASSERT_EQ(pipeOut2.size(), 3);  
    ASSERT_EQ(pipeIn.size(), 0);   
}

