#include "gtest/gtest.h"
#include "utils/measurer.h"
TEST(Measurer, pause)
{
    khustup::utils::Measurer measurer;
    measurer.pause();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_GT(10, measurer.getElapsedTimeInMilliseconds()) << "elapsed time should be less than 10 milliseconds";

    measurer.resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_GE(measurer.getElapsedTimeInMilliseconds(), 10) << "elapsed time should be greater than 10 milliseconds";
    
    measurer.reset();
    EXPECT_LT(measurer.getElapsedTimeInMilliseconds(), 1) << "elapsed time should be less than 1 millisecond";
}