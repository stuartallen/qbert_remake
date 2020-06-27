cmake_minimum_required(VERSION 3.14)
project(qbert VERSION 0.1.0)

# use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(qbert 
  application.cpp board.cpp sound.cpp creature.cpp player.cpp
  )

# ======================================================================
# SDL2 
# **** NEED TO DO THIS YOURSELF ****
# WINDOWS: 
#   1) extract https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip and install here
#   2) put sdl2-config.cmake in that SDL_ROOT
# MAC: 
#   1) brew install sdl2 sdl2_gfx SDL2_mixer
#   2) edit SDL2_DIR if necessary

# ======================================================================
# Download and unzip all external libraries
#
# found at https://www.scivision.dev/cmake-download-verify-file/
function(download_file url filename hash_type hash)

if(NOT EXISTS ${filename})
  message("downloading " ${url})
  file(DOWNLOAD ${url} ${filename}
       TIMEOUT 60  # seconds
       EXPECTED_HASH ${hash_type}=${hash}
       TLS_VERIFY ON)
endif()

endfunction(download_file)

# ======================================================================
function(extract_zip zipfile outfile)

if(NOT EXISTS ${outfile})
  message("unzipping   " ${outfile})
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${zipfile} 
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

endfunction(extract_zip)

# ======================================================================
# I think "APPLE" is the way to check for mac...
if(APPLE)
  set( SDL2_DIR /usr/local/Cellar/sdl2/2.0.12_1 )
  set( SDL2_GFX_DIR /usr/local/Cellar/sdl2_gfx/1.0.4 )
  set( SDL2_MIXER_DIR /usr/local/Cellar/sdl2_mixer/2.0.4 )
elseif(WIN32)
    set( SDL_URL    https://www.libsdl.org/release/SDL2-devel-2.0.12-VC.zip )
    set( SDL_ZIP    ${CMAKE_CURRENT_SOURCE_DIR}/SDL2-devel-2.0.12-VC.zip )
    set( SDL_ROOT   ${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.0.12 )
    set( SDL_MD5    c2262a2f2d4e8487b75b541bfee3c2c4 )
    download_file( ${SDL_URL} ${SDL_ZIP} MD5 ${SDL_MD5} )
    extract_zip( ${SDL_ZIP} ${SDL_ROOT} )
    if(NOT EXISTS ${SDL_ROOT}/sdl2-config.cmake)
       file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sdl2-config.cmake DESTINATION ${SDL_ROOT}) 
    endif()
  set( SDL2_DIR ${SDL_ROOT} )
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
# workaround for CMP0004 issue with the SDL2 libraries on Linux
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(qbert ${SDL2_LIBRARIES})

include_directories(${SDL2_GFX_DIR}/include/SDL2 )
target_link_libraries(qbert -L${SDL2_GFX_DIR}/lib )
target_link_libraries(qbert -lSDL2_gfx )

include_directories(${SDL2_MIXER_DIR}/include/SDL2 )
target_link_libraries(qbert -L${SDL2_MIXER_DIR}/lib )
target_link_libraries(qbert -lSDL2_mixer )

# Windows: copy the dll as a post-build step
if(WIN32)
    add_custom_command(TARGET qbert POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
             "${SDL2_DIR}/lib/x64/SDL2.dll"
             $<TARGET_FILE_DIR:qbert>)
endif()