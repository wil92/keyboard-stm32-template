project(tests_run)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(tests_run KeyboardTest.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(tests_run del_lib)

target_link_libraries(tests_run gtest gtest_main)
