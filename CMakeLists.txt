cmake_minimum_required(VERSION 3.29)
project(SentenceGeneratorForCharades)

set(CMAKE_CXX_STANDARD 20)

include_directories(include sqlite)

add_executable(SentenceGeneratorForCharades main.cpp
                sqlite/sqlite3.h sqlite/sqlite3.c
                src/Server.cpp
                src/RatingDao.cpp src/WordDao.cpp
                src/FileReader.cpp src/CFG.cpp
)
