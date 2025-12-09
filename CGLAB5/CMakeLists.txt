cmake_minimum_required(VERSION 3.28)
project(lb5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

find_package(OpenGL REQUIRED)

add_executable(lb5 main.cpp camera.cpp)

include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(lb5 ${OPENGL_LIBRARIES} winmm)

add_custom_command(TARGET lb5 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        #        "O:\\Program Files\\CodeBlocks\\libwinpthread-1.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/libwinpthread-1.dll"
        $<TARGET_FILE_DIR:lb5>
)
