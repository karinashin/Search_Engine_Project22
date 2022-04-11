cmake_minimum_required(VERSION 3.16)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 14)

configure_file(test.json COPYONLY)

#add_executable(22s_final_proj main.cpp catch_setup.cpp DSAVLTree.h DocParser.cpp DocParser.h Word.cpp Word.h Document.cpp Document.h catchTests.cpp)
add_executable(22s_final_proj main.cpp DSAVLTree.h DocParser.cpp DocParser.h Word.cpp Word.h Document.cpp Document.h)
