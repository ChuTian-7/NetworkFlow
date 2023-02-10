# brute force test
ADD_EXECUTABLE(bruteforceTest brute_force_test.cpp)
TARGET_LINK_LIBRARIES(bruteforceTest graph_src brute_force_src testa LYalgorithm)
ADD_TEST(NAME bruteforceTest COMMAND bruteforceTest)
TARGET_INCLUDE_DIRECTORIES(bruteforceTest PUBLIC ../AHO-MS2003/src)

# cost scaling test
ADD_EXECUTABLE(costscalingTest cost_scaling_test.cpp)
TARGET_LINK_LIBRARIES(costscalingTest cost_scaling_src brute_force_src testa LYalgorithm)
ADD_TEST(NAME costscalingTest COMMAND costscalingTest)
TARGET_INCLUDE_DIRECTORIES(costscalingTest PUBLIC ../AHO-MS2003/src)

# min25 test
ADD_EXECUTABLE(min25Test min25_test.cpp)
ADD_TEST(NAME min25Test COMMAND min25Test)

# lemon test
ADD_EXECUTABLE(lemonTest lemon_test.cpp)
ADD_TEST(NAME lemonTest COMMAND lemonTest)
TARGET_INCLUDE_DIRECTORIES(lemonTest PUBLIC /usr/local/share/lemon)