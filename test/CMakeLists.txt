# brute force test
ADD_EXECUTABLE(bruteforceTest brute_force_test.cpp)
TARGET_LINK_LIBRARIES(bruteforceTest graph_src brute_force_src)
ADD_TEST(NAME bruteforceTest COMMAND bruteforceTest)
