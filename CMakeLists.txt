cmake_minimum_required(VERSION 3.29)
project(SentenceGeneratorForCharades)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(SentenceGeneratorForCharades main.cpp src/Server.cpp)
