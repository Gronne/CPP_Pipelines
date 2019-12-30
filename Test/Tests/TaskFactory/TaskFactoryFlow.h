#include "../ClassHeader.h"


TEST(TaskFactoryTestFlow, flow_one_task)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            int buffer;
            while(!in.eof())
            {
                if((in >> buffer) == false)
                    continue;
                
                out << buffer;
            }

            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn = {1, 2, 3};
    pipeIn.set_eof();

    PLS::PipeQueue<int> pipeOut;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f));


    PLS::PipeQueue<int> pipeCompare = {1, 2, 3};
    ASSERT_TRUE(pipeOut == pipeCompare);  
}


TEST(TaskFactoryTestFlow, flow_two_tasks)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            int buffer;
            while(!in.eof())
            {
                if((in >> buffer) == false)
                    continue;
                
                out << buffer;
            }

            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn = {1, 2, 3};
    pipeIn.set_eof();

    PLS::PipeQueue<int> pipeOut1, pipeOut2;

    std::future<void> f1, f2;

    ASSERT_NO_THROW(f1 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut1));
    ASSERT_NO_THROW(f2 = PLS::TaskFactory::start_async_task(lambdaFunction, pipeOut1, pipeOut2));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f1, f2));

    PLS::PipeQueue<int> pipeCompare = {1, 2, 3};
    ASSERT_TRUE(pipeOut2 == pipeCompare);  
}


TEST(TaskFactoryTestFlow, flow_two_tasks_one_inputPipe)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            int buffer;
            while(!in.eof())
            {
                if((in >> buffer) == false)
                    continue;
                
                out << buffer;
            }

            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn = {1, 2, 3, 4};
    pipeIn.set_eof();

    PLS::PipeQueue<int> pipeOut1, pipeOut2;

    std::future<void> f1, f2;

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
                if((in >> buffer) == false)
                    continue;

                ASSERT_NO_THROW(outA << buffer);
                ASSERT_NO_THROW(outB << buffer);
            }
            
            outA.set_eof();
            outB.set_eof();
        };

    PLS::PipeQueue<int> pipeIn = {1, 2, 3};
    pipeIn.set_eof();

    PLS::PipeQueue<int> pipeOut1, pipeOut2;

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::start_async_task(lambdaFunction, pipeIn, pipeOut1, pipeOut2));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f));

    PLS::PipeQueue<int> pipeCompare = {1, 2, 3};
    ASSERT_TRUE(pipeOut1 == pipeCompare);  
    ASSERT_TRUE(pipeOut2 == pipeCompare);  
    ASSERT_EQ(pipeIn.size(), 0);   
}

