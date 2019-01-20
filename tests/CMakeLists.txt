file(GLOB test_sources "*.cpp" "*.hpp")
add_executable(${PROJECT_NAME}.tests ${test_sources})

set_target_properties(${PROJECT_NAME}.tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

enable_testing()
add_test(${PROJECT_NAME}.tests ${PROJECT_NAME})
