cmake_minimum_required(VERSION 3.10)
 
set(PROJECT_NAME BoardGameClient)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Client)
 
# set the project name and version
project(${PROJECT_NAME}
        VERSION 1.0
        LANGUAGES CXX)

# find source
file(GLOB_RECURSE SOURCES
     ${SOURCE_DIR}/*.cpp)

# add subprojects
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../third-party/DawnStar/DawnStar third-party/DawnStar)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../DawnBoard DawnBoard)

# make exe file
add_compile_definitions(DS_DEBUG)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})

# Linking
target_link_libraries(${PROJECT_NAME} DawnStar DawnBoard)

# compile option for c17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)