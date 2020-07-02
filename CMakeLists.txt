cmake_minimum_required(VERSION 3.14)
project(qbert VERSION 0.1.0)

# use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(qbert 
  application.cpp board.cpp sound.cpp creature.cpp player.cpp
  spriteSheet.cpp
  )

# ======================================================================
# SDL2 
# **** NEED TO DO THIS YOURSELF ****
# WINDOWS: 
#   1) vcpkg install sdl2 sdl2-gfx sdl2-mixer
#   2) be sure path to vcpkg "toolchainFile" is set via "Edit Local CMake Kits"
#   2) set x86 build target
#   
# MAC: 
#   1) brew install sdl2 sdl2_gfx SDL2_mixer
#   2) edit SDL2_DIR if necessary

# ======================================================================
# I think "APPLE" is the way to check for mac...
if(APPLE)
  set( SDL2_DIR /usr/local/Cellar/sdl2/2.0.12_1 )
  set( SDL2_GFX_DIR /usr/local/Cellar/sdl2_gfx/1.0.4 )
  set( SDL2_MIXER_DIR /usr/local/Cellar/sdl2_mixer/2.0.4 )

  find_package(SDL2 REQUIRED)
  include_directories(${SDL2_INCLUDE_DIRS})
  # workaround for CMP0004 issue with the SDL2 libraries on Linux
  string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
  target_link_libraries(qbert ${SDL2_LIBRARIES})

  include_directories(${SDL2_GFX_DIR}/include/SDL2 )
  include_directories(${SDL2_MIXER_DIR}/include/SDL2 )

  target_link_libraries(qbert -L${SDL2_GFX_DIR}/lib )
  target_link_libraries(qbert -lSDL2_gfx )
  target_link_libraries(qbert -L${SDL2_MIXER_DIR}/lib )
  target_link_libraries(qbert -lSDL2_mixer )

elseif(WIN32)

  find_package(SDL2 CONFIG REQUIRED)
  target_link_libraries(qbert PRIVATE SDL2::SDL2 SDL2::SDL2main)

  find_package(sdl2-gfx CONFIG REQUIRED)
  target_link_libraries(qbert PRIVATE SDL2::SDL2_gfx)

  find_package(sdl2-mixer CONFIG REQUIRED)
  target_link_libraries(qbert PRIVATE SDL2::SDL2_mixer)

endif()
