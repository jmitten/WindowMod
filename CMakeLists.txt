cmake_minimum_required(VERSION 3.3)
project(WindowMod)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libstdc++ -static-libgcc -s -Os")
set(SOURCE_FILES main.cpp)
add_executable(WindowMod ${SOURCE_FILES} res/WindowMod.rc)
add_custom_command(TARGET WindowMod POST_BUILD
      COMMAND upx.exe ARGS $<TARGET_FILE:WindowMod> --best
        COMMENT "Compressing executable file")
add_custom_command(TARGET WindowMod POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_FILE:WindowMod>"
        "${PROJECT_SOURCE_DIR}/bin/release/$<TARGET_FILE_NAME:WindowMod>"
        COMMENT "Copying compressed file to output directory ${PROJECT_SOURCE_DIR}/bin/release/")