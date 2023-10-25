cmake_minimum_required(VERSION 3.10)
 
set(PROJECT_NAME BoardGameClient)
 
# set the project name and version
project(${PROJECT_NAME}
        VERSION 1.0
        LANGUAGES CXX)

# find source
file(GLOB_RECURSE SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# add subprojects
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/DawnStar/DawnStar)

# make exe file
# message("Hello", ${SOURCES})
add_compile_definitions(DS_DEBUG)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Linking
target_link_libraries(${PROJECT_NAME} DawnStar)

# compile option for c17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)