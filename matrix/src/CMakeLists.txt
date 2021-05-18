project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES Matrix.h)
set(SOURCE_FILES Matrix.cpp)

# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )
