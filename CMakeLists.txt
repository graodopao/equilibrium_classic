cmake_minimum_required(VERSION 3.7)
include(CMakePrintHelpers)


project(Equilibrium)

find_package(SDL2 REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

cmake_print_variables(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES
        "src/nashira/*.h"
        "src/nashira/*.hpp"
        "src/nashira/*.cpp"
        "src/*.h"
        "src/*.hpp"
        "src/*.cpp"
        "*.h"
        "*.hpp"
        "*.cpp"
)

add_executable(Equilibrium ${SOURCES})
target_link_libraries(Equilibrium PRIVATE
        ${SDL2_LIBRARIES}
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)



