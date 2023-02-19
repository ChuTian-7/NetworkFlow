# brute force test
ADD_EXECUTABLE(bruteforceTest brute_force_test.cpp)
TARGET_LINK_LIBRARIES(bruteforceTest graph_src brute_force_src testa aho_ms2003)
ADD_TEST(NAME bruteforceTest COMMAND bruteforceTest)
TARGET_INCLUDE_DIRECTORIES(bruteforceTest PUBLIC ../AHO-MS2003/src ../AHO-MS2003/src/include)

# cost scaling test
ADD_EXECUTABLE(costscalingTest cost_scaling_test.cpp)
TARGET_LINK_LIBRARIES(costscalingTest brute_force_src testa aho_ms2003 problem_src generator_src)
ADD_TEST(NAME costscalingTest COMMAND costscalingTest)
TARGET_INCLUDE_DIRECTORIES(costscalingTest PUBLIC ../AHO-MS2003/src ../AHO-MS2003/src/include)

# min25 test
ADD_EXECUTABLE(min25Test min25_test.cpp)
ADD_TEST(NAME min25Test COMMAND min25Test)

#testa test
add_executable(testaTest testa_test.cpp)
TARGET_LINK_LIBRARIES(testaTest testa brute_force_src testa aho_ms2003 problem_src generator_src)
target_include_directories(testaTest PUBLIC ../include ../testa/cpp ../AHO-MS2003/src ../AHO-MS2003/src/include)
