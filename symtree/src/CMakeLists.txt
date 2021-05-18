project(${CMAKE_PROJECT_NAME}_lib)

set(SOURCE expression.h number.h number.cpp binaryExpression.h variable.cpp variable.h)
# The library contains header and source files.
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCE})