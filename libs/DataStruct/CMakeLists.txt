cmake_minimum_required(VERSION 3.1.0)
project("DataStruct"
        LANGUAGES "C"
)

set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/datastruct.c
)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(DS_LIB ${PROJECT_NAME}_lib)

macro(subdirlist RESULT CURDIR)
    file(GLOB CHILDREN RELATIVE ${CURDIR} ${CURDIR}/*)
    set(DIRLIST "")
    foreach (CHILD ${CHILDREN})
        if(IS_DIRECTORY ${CURDIR}/${CHILD} AND EXISTS ${CURDIR}/${CHILD}/CMakeLists.txt)
        list(APPEND DIRLIST "${CURDIR}/${CHILD}")
    endif()
    endforeach()
    set(${RESULT} ${DIRLIST})
endmacro()

subdirlist(SUBDIRS ${PROJECT_SOURCE_DIR}/libs)
set(DS_LIBRARIES)
set(INCLUDE_STATEMENTS)

foreach(SUBDIR ${SUBDIRS})
    add_subdirectory(${SUBDIR})
endforeach()

configure_file(${PROJECT_SOURCE_DIR}/include/ds_headers.h.in ${PROJECT_SOURCE_DIR}/include/ds_headers.h)

target_link_libraries(${DS_LIB} ${DS_LIBRARIES})

set(LIBRARIES ${LIBRARIES} ${DS_LIB} PARENT_SCOPE)
