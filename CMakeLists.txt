cmake_minimum_required(VERSION 3.27)
project(bengine CXX)

if(MSVC)
    add_compile_options(/arch:AVX2)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED on)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE INC_FILES "src/*.hpp")
file(GLOB_RECURSE DEP_SRC_FILES "dep/SimpleMath/*.cpp")

include_directories("src")
include_directories("dep/SimpleMath")
include_directories("dep/tinygltf")

foreach(SRC_FILE ${SRC_FILES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/src" ${SRC_FILE})
    string(REPLACE "/" "\\" GROUP_NAME "${REL_PATH}")
    get_filename_component(GROUP_NAME "${GROUP_NAME}" PATH)
    source_group("Sources\\${GROUP_NAME}" FILES "${SRC_FILE}")
endforeach()

foreach(INC_FILE ${INC_FILES})
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/src" ${INC_FILE})
    string(REPLACE "/" "\\" GROUP_NAME "${REL_PATH}")
    get_filename_component(GROUP_NAME "${GROUP_NAME}" PATH)
    source_group("Headers\\${GROUP_NAME}" FILES "${INC_FILE}")
endforeach()

add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES} ${DEP_SRC_FILES})
target_link_libraries(${PROJECT_NAME} d3d11 dxgi d3dcompiler)

target_precompile_headers(${PROJECT_NAME} PRIVATE "src/pch.h")
