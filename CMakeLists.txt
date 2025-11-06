cmake_minimum_required(VERSION 3.14)

project(magos-project VERSION 0.1 DESCRIPTION "Game Engine" LANGUAGES CXX)

set(SOURCES
    Sandbox/src/Application.cpp
)

add_executable(MyExit ${SOURCES})

# find_package(SomeLibrary REQUIRED)
# target_link_libraries(MyExit PRIVATE SomeLibrary::SomeLibrary)

# enable_testing()
# add_executable(MyTest tests/test_main.cpp)
# target_link_libraries(MyTest PRIVATE MyExit)
# add_test(NAME MyTest COMMAND MyTest)