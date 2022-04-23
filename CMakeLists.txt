cmake_minimum_required(VERSION 3.16)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 17)

#add_executable(22s_final_proj main.cpp catch_setup.cpp DSAVLTree.h DocParser.cpp DocParser.h Word.cpp Word.h Document.cpp Document.h catchTests.cpp)
add_executable(22s_final_proj main.cpp DSAVLTree.h DocParser.cpp DocParser.h Word.cpp Word.h Document.cpp Document.h porter2_stemmer.cpp porter2_stemmer.h QueryProcessor.cpp QueryProcessor.h UserInterface.cpp UserInterface.h)
