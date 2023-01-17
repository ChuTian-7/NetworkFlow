ADD_LIBRARY(graph_src graph.cpp)
ADD_LIBRARY(brute_force_src brute_force.cpp)


TARGET_INCLUDE_DIRECTORIES(graph_src PUBLIC ../include)
TARGET_INCLUDE_DIRECTORIES(brute_force PUBLIC ../include)