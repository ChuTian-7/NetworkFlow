# brute force test
ADD_EXECUTABLE(bruteforceTest brute_force_test.cpp)
TARGET_LINK_LIBRARIES(bruteforceTest graph_src brute_force_src problem_solver_src testa)
ADD_TEST(NAME bruteforceTest COMMAND bruteforceTest)

# cost scaling test
ADD_EXECUTABLE(costscalingTest cost_scaling_test.cpp)
TARGET_LINK_LIBRARIES(costscalingTest cost_scaling_src brute_force_src)
ADD_TEST(NAME costscalingTest COMMAND costscalingTest)

# min25 test
ADD_EXECUTABLE(min25Test min25_test.cpp)
ADD_TEST(NAME min25Test COMMAND min25Test)
