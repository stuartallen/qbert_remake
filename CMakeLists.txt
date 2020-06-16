cmake_minimum_required(VERSION 3.14)
project(qbert VERSION 0.1.0)

# use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(qbert 
  application.cpp board.cpp
  )

# ======================================================================
# SDL2 
# **** NEED TO DO THIS YOURSELF ****
# WINDOWS: 
#   1) extract https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip and install here
#   2) put sdl2-config.cmake in that SDL_ROOT
# MAC: 
#   1) brew install sdl2 sdl2_gfx
#   2) edit SDL2_DIR if necessary
if(WIN32)
  set( SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.12 )
endif()
# FIXME -- what is this supposed to be?
#if(MAC)
  set( SDL2_DIR /usr/local/Cellar/sdl2/2.0.12_1 )
  set( SDL2_GFX_DIR /usr/local/Cellar/sdl2_gfx/1.0.4 )
#endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
# workaround for CMP0004 issue with the SDL2 libraries on Linux
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(qbert ${SDL2_LIBRARIES})

include_directories(${SDL2_GFX_DIR}/include/SDL2 )
target_link_libraries(qbert -L${SDL2_GFX_DIR}/lib )
target_link_libraries(qbert -lSDL2_gfx )


# Windows: copy the dll as a post-build step
if(WIN32)
    add_custom_command(TARGET qbert POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
             "${SDL2_DIR}/lib/x64/SDL2.dll"
             $<TARGET_FILE_DIR:qbert>)
endif()