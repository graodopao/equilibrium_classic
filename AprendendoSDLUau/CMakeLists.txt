cmake_minimum_required(VERSION 3.7)
include(CMakePrintHelpers)


project(AprendendoSDLUau)

find_package(SDL2 REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

cmake_print_variables(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES
    "*.h"
    "*.cpp"
)

add_executable(AprendendoSDLUau ${SOURCES})
target_link_libraries(AprendendoSDLUau PRIVATE
        ${SDL2_LIBRARIES}
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)



