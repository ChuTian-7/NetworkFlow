# brute force test
ADD_EXECUTABLE(bruteforceTest brute_force_test.cpp)
TARGET_LINK_LIBRARIES(bruteforceTest graph_src brute_force_src problem_solver_src testa)
ADD_TEST(NAME bruteforceTest COMMAND bruteforceTest)

# problem part test
ADD_EXECUTABLE(problempartTest problem_part_test.cpp)
TARGET_LINK_LIBRARIES(problempartTest graph_src problem_src)
ADD_TEST(NAME problempartTest COMMAND problempartTest)

# cost scaling test
ADD_EXECUTABLE(costscalingTest cost_scaling_test.cpp)
TARGET_LINK_LIBRARIES(costscalingTest cost_scaling_src)
ADD_TEST(NAME costscalingTest COMMAND costscalingTest)

# min25 test
ADD_EXECUTABLE(min25Test min25_test.cpp)
ADD_TEST(NAME min25Test COMMAND min25Test)

# new cs test
ADD_EXECUTABLE(newcsTest new_cs_test.cpp)
TARGET_LINK_LIBRARIES(newcsTest cost_scaling_src brute_force_src)
ADD_TEST(NAME newcsTest COMMAND newcsTest)