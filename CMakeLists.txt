cmake_minimum_required(VERSION 3.28)
project(SterdomServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE DEBUG)

# set include directories
set(SrcDIR ${CMAKE_SOURCE_DIR}/src)
set(IncludeDIR ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)

include_directories(
        ${SrcDIR}
        ${IncludeDIR}
)

# search for packages

# websocketpp
find_package(websocketpp REQUIRED)
include_directories(${WEBSOCKETPP_INCLUDE_DIR})

# nlohmann_json
find_package(nlohmann_json 3.2.0 REQUIRED)
include_directories(${NLOHMANN_JSON_INCLUDE_DIR})

# curl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

file(GLOB_RECURSE SOURCE_FILES ${SrcDIR}/*.cpp ${SrcDIR}/*.c ${SrcDIR}/**/*.cpp ${SrcDIR}/**/*.c)
file(GLOB_RECURSE HEADER_FILES ${SrcDIR}/*.h ${SrcDIR}/*.hpp ${SrcDIR}/**/*.h ${SrcDIR}/**/*.hpp)

add_executable(sterdomserver ${CMAKE_SOURCE_DIR}/src/main.cpp ${SOURCE_FILES})
target_link_directories(sterdomserver PUBLIC ${CMAKE_SOURCE_DIR}/src/)

# link packages

# websocketpp
target_link_libraries(sterdomserver ${WEBSOCKETPP_LIBRARY})

# nlohmann_json
target_link_libraries(sterdomserver ${NLOHMANN_JSON_LIBRARY})

# curl
target_link_libraries(sterdomserver ${CURL_LIBRARY})


install(TARGETS sterdomserver DESTINATION ${CMAKE_INSTALL_BINDIR})