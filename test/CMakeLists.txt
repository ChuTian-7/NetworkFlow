# brute force test
ADD_EXECUTABLE(bruteforceTest brute_force_test.cpp)
TARGET_LINK_LIBRARIES(bruteforceTest graph_src brute_force_src problem_solver_src testa)
ADD_TEST(NAME bruteforceTest COMMAND bruteforceTest)

# problem part test
ADD_EXECUTABLE(problempartTest problem_part_test.cpp)
TARGET_LINK_LIBRARIES(problempartTest graph_src problem_src)
ADD_TEST(NAME problempartTest COMMAND problempartTest)