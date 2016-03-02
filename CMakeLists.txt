project(lua-intf-tests)
cmake_minimum_required(VERSION 2.8)

set(USE_LUAJIT TRUE)

file(
  GLOB_RECURSE
  SRC_LIST
  #LuaIntf/*.cpp
  LuaIntf/*.h
)

file(
    GLOB_RECURSE
    SCRIPTS
    *.lua
)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wno-c++11-narrowing")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#include_directories("${PROJECT_BINARY_DIR}")
include_directories(
  ${PROJECT_SOURCE_DIR}/LuaIntf
  #${PROJECT_SOURCE_DIR}
  #${PROJECT_BINARY_DIR}/include
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

file(COPY ${SCRIPTS} DESTINATION .)

if(USE_LUAJIT)
    find_package(LuaJIT)
    if(LUAJIT_FOUND)
	include_directories(${LUAJIT_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${LUAJIT_LIBRARIES})
	add_definitions(-DLUAINTF_USELUAJIT)
        message("Using LuaJIT  " ${LUAJIT_INCLUDE_DIR} "  " ${LUAJIT_LIBRARIES})
    endif()
else()
    find_package(Lua)
    if(LUA_FOUND)
	include_directories(${LUA_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})
        message("Using default Lua  " ${LUA_LIBRARIES} "   " ${LUA_INCLUDE_DIR})
    endif()
endif()

