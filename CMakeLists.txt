cmake_minimum_required(VERSION 3.10)

project(LoanIt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LoanIt main.cpp autoincrementable.cpp cli.cpp databaseparentawarable.cpp filehandler.cpp item.cpp loan.cpp loanschema.cpp record.cpp)
