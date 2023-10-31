cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME DawnBoard)

project(${PROJECT_NAME}
        VERSION 1.0
        LANGUAGES CXX)


file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/*.cpp)
    
# make library file
add_library(${PROJECT_NAME} STATIC 
            ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR})
                           
# compile option for c17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)