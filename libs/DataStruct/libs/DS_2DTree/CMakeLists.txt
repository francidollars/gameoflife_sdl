cmake_minimum_required(VERSION 3.1.0)
project("DS_2DTree"
    LANGUAGES "C"
)

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/ds_twodim_tree.c
)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}_lib ${DS_LIB})

set(DS_LIBRARIES ${DS_LIBRARIES} ${PROJECT_NAME}_lib PARENT_SCOPE)

file(GLOB INCLUDE_FILES RELATIVE ${PROJECT_SOURCE_DIR}/include include/${PROJECT_NAME}/*.h)
foreach(INCLUDE_FILE ${INCLUDE_FILES})
    set(INCLUDE_STATEMENTS "${INCLUDE_STATEMENTS}#include \"${INCLUDE_FILE}\"\n" PARENT_SCOPE)
endforeach()
