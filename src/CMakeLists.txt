cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

include(CTest)
set(C_STANDARD C99)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR})
add_executable(ex2 main.cpp bmp_tester.cpp BitAdjuster.cpp Bitmap.cpp BitmapHeader.cpp BitmapDIBHeader.cpp 
ColorPallete.cpp BitmapArray.cpp Matrix.cpp ErrorCode.cpp)
target_link_libraries(ex2 matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
