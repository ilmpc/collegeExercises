project(${CMAKE_PROJECT_NAME}_lib)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(HEADER_FILES agent.h worker.h)
set(SOURCE_FILES agent.cpp worker.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES} ${HEADER_FILES} )
target_link_libraries(${CMAKE_PROJECT_NAME}_lib Threads::Threads)