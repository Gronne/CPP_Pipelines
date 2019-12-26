#include <gtest/gtest.h>

#include "PipeQueue/PipeQueueTests.h"
#include "TaskFactory/TaskFactoryTests.h"




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}