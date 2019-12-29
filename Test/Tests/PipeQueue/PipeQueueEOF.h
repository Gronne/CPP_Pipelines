#include "../ClassHeader.h"


TEST(PipeQueueTestEOF, EOF_empty_pipe)
{
    PLS::PipeQueue<int> pipe;

    ASSERT_NO_THROW(pipe.eof());
    ASSERT_FALSE(pipe.eof());
}


TEST(PipeQueueTestEOF, EOF_filled_pipe)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};

    ASSERT_NO_THROW(pipe.eof());
    ASSERT_FALSE(pipe.eof());
}


TEST(PipeQueueTestEOF, EOF_emptied_pipe)
{
    PLS::PipeQueue<int> pipe = {1};
    
    int buffer;
    pipe.try_pop(buffer);

    ASSERT_NO_THROW(pipe.eof());
    ASSERT_FALSE(pipe.eof());
}


TEST(PipeQueueTestEOF, EOF_empty_pipe_set)
{
    PLS::PipeQueue<int> pipe;
    pipe.set_eof();

    ASSERT_NO_THROW(pipe.eof());
    ASSERT_TRUE(pipe.eof());
}


TEST(PipeQueueTestEOF, EOF_filled_pipe_set)
{
    PLS::PipeQueue<int> pipe = {1, 2, 3};
    pipe.set_eof();

    ASSERT_NO_THROW(pipe.eof());
    ASSERT_FALSE(pipe.eof());
}


TEST(PipeQueueTestEOF, EOF_emptied_pipe_set)
{
    PLS::PipeQueue<int> pipe = {1};
    pipe.set_eof();

    ASSERT_FALSE(pipe.eof());

    int buffer;
    pipe.try_pop(buffer);

    ASSERT_NO_THROW(pipe.eof());
    ASSERT_TRUE(pipe.eof());
}


TEST(PipeQueueTestEOF, EOF_true_to_false)
{
   PLS::PipeQueue<int> pipe;
    pipe.set_eof();

    ASSERT_TRUE(pipe.eof());

    pipe.push(5);

    ASSERT_NO_THROW(pipe.eof());
    ASSERT_FALSE(pipe.eof());
}
