project(gtarma-dl)

cmake_minimum_required(VERSION 3.9)

add_definitions(-DCURL_STATICLIB)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DCURL_STATICLIB")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CURL_STATICLIB ON CACHE BOOL "Enable static lib")

file(GLOB_RECURSE gtarma-dl_SRC
"src/*.cpp"
)

file(GLOB_RECURSE gtarma-dl_HEADER
"include/*.h"
)

include_directories("include")
include_directories("externals/rapidjson/include")

#add_executable(${PROJECT_NAME} ${gtarma-dl_SRC} ${gtarma-dl_HEADER})
add_library(${PROJECT_NAME} SHARED ${gtarma-dl_SRC} ${gtarma-dl_HEADER})

add_subdirectory(externals/cpr)

target_link_libraries(gtarma-dl ${CPR_LIBRARIES} ${CURL_LIBRARY})