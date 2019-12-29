#include "../ClassHeader.h"


TEST(TaskFactoryTestFlow, flow_one_task)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            while(!in.eof())
            {
                ASSERT_NO_THROW(out.push_back(in.front()));
                ASSERT_NO_THROW(in.pop_front());
            }
            
            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn, pipeOut;

    pipeIn.push_back(1);
    pipeIn.push_back(2);
    pipeIn.push_back(3);

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::startAsyncTask(lambdaFunction, pipeIn, pipeOut));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f));


    ASSERT_EQ(pipeOut.size(), 3);       //== will make this easier
    ASSERT_EQ(pipeOut.front(), 1);
    pipeOut.pop_front();
    ASSERT_EQ(pipeOut.front(), 2);
    pipeOut.pop_front();
    ASSERT_EQ(pipeOut.front(), 3);
    pipeOut.pop_front();
}


TEST(TaskFactoryTestFlow, flow_two_tasks)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            while(!in.eof())
            {
                ASSERT_NO_THROW(out.push_back(in.front()));
                ASSERT_NO_THROW(in.pop_front());
            }
            
            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn, pipeOut1, pipeOut2;

    pipeIn.push_back(1);
    pipeIn.push_back(2);
    pipeIn.push_back(3);

    std::future<void> f1;
    std::future<void> f2;

    ASSERT_NO_THROW(f1 = PLS::TaskFactory::startAsyncTask(lambdaFunction, pipeIn, pipeOut1));
    ASSERT_NO_THROW(f2 = PLS::TaskFactory::startAsyncTask(lambdaFunction, pipeOut1, pipeOut2));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f1, f2));

    ASSERT_EQ(pipeOut2.size(), 3);       //== will make this easier
    ASSERT_EQ(pipeOut2.front(), 1);
    pipeOut2.pop_front();
    ASSERT_EQ(pipeOut2.front(), 2);
    pipeOut2.pop_front();
    ASSERT_EQ(pipeOut2.front(), 3);
    pipeOut2.pop_front();
}


TEST(TaskFactoryTestFlow, flow_two_tasks_one_inputPipe)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &out) 
        { 
            while(!in.eof())
            {
                ASSERT_NO_THROW(out.push_back(in.front()));
                ASSERT_NO_THROW(in.pop_front());
            }
            
            out.set_eof();
        };

    PLS::PipeQueue<int> pipeIn, pipeOut1, pipeOut2;

    pipeIn.push_back(1);
    pipeIn.push_back(2);
    pipeIn.push_back(3);
    pipeIn.push_back(4);

    std::future<void> f1;
    std::future<void> f2;

    ASSERT_NO_THROW(f1 = PLS::TaskFactory::startAsyncTask(lambdaFunction, pipeIn, pipeOut1));
    ASSERT_NO_THROW(f2 = PLS::TaskFactory::startAsyncTask(lambdaFunction, pipeIn, pipeOut2));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f1, f2));

    ASSERT_EQ(pipeOut1.size() + pipeOut2.size(), 4);
    ASSERT_EQ(pipeIn.size(), 0);
}


TEST(TaskFactoryTestFlow, flow_one_tasks_two_pipes)
{
    decltype(auto) lambdaFunction = [](PLS::PipeQueue<int> &in, PLS::PipeQueue<int> &outA, PLS::PipeQueue<int> &outB) 
        { 
            while(!in.eof())
            {
                ASSERT_NO_THROW(outA.push_back(in.front()));
                ASSERT_NO_THROW(outB.push_back(in.front()));
                ASSERT_NO_THROW(in.pop_front());
            }
            
            outA.set_eof();
            outB.set_eof();
        };

    PLS::PipeQueue<int> pipeIn, pipeOut1, pipeOut2;

    pipeIn.push_back(1);
    pipeIn.push_back(2);
    pipeIn.push_back(3);

    std::future<void> f;
    ASSERT_NO_THROW(f = PLS::TaskFactory::startAsyncTask(lambdaFunction, pipeIn, pipeOut1, pipeOut2));
    ASSERT_NO_THROW(PLS::TaskFactory::wait_all(f));

    ASSERT_EQ(pipeOut1.size(), 3);  
    ASSERT_EQ(pipeOut2.size(), 3);  
    ASSERT_EQ(pipeIn.size(), 0);   
}