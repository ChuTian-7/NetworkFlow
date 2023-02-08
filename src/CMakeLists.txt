ADD_LIBRARY(graph_src graph.cpp)
ADD_LIBRARY(brute_force_src brute_force.cpp)
ADD_LIBRARY(cost_scaling_src cost_scaling.cpp graph.cpp)

TARGET_INCLUDE_DIRECTORIES(graph_src PUBLIC ../include)
TARGET_INCLUDE_DIRECTORIES(brute_force_src PUBLIC ../include)
TARGET_INCLUDE_DIRECTORIES(cost_scaling_src PUBLIC ../include)