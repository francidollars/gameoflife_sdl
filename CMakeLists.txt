cmake_minimum_required(VERSION 3.1.0)
project(GameOfLife_SDL
        VERSION 0.1.0
        LANGUAGES "C"
)

list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_SOURCE_DIR}/cmake"
        "${CMAKE_SOURCE_DIR}/cmake/FindModules/sdl2"
)

# include(CTest)
# enable_testing()
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")

set(SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/sdl_funcs.c
        ${PROJECT_SOURCE_DIR}/src/SDL_FontCache.c       # TODO: Files below this point should be public/excluded from essential headers
)                                                       #       or go into own libraries (each ds has own library)


add_library(GOLSDL_lib STATIC ${SOURCE_FILES})
target_include_directories(GOLSDL_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}_bin ${PROJECT_SOURCE_DIR}/src/main.c)
set_target_properties(${PROJECT_NAME}_bin PROPERTIES LINKER_LANGUAGE C)

set(LIBRARIES GOLSDL_lib)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/DataStruct)

target_link_libraries(${PROJECT_NAME}_bin ${LIBRARIES})

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME}_bin SDL2::Main)

# Add SDL2_image library
#find_package(SDL2_image REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Image)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME}_bin SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
#find_package(SDL2_gfx REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::GFX)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
