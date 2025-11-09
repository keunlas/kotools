add_executable(test_taskqueue taskqueue.cpp)
target_link_libraries(test_taskqueue PRIVATE kotools)
# add_test(NAME "taskqueue_api" COMMAND test_taskqueue)
