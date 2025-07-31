include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        ThreeDArray_tests
        ThreeDArray_test.cpp
        ThreeDArray_test.cpp
)

target_link_libraries(
        ThreeDArray_tests
        ThreeDArray
        GTest::gtest_main
)

target_include_directories(ThreeDArray_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(ThreeDArray_tests)