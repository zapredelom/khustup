#include "gtest/gtest.h"
#include "utils/measurer.h"
TEST(Measurer, pause)
{
    khustup::utils::Measurer measurer;
    measurer.pause();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_GT(10, measurer.getElapsedTimeInMilliseconds());
}