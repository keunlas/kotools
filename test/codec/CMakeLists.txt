add_executable(test_base64 base64.cpp)
target_link_libraries(test_base64 PRIVATE kotools)
add_test(NAME "base64_api" COMMAND test_base64)

