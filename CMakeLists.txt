#@ Author       "Ryan McClue" <mcclue.ryan@gmail.com>
#@ Description  Cross platform 2D SDL game.
#@ Usage: 
#@	 mkdir build/ && cd build/ && cmake .. 
#@   ctest <name>
#@   cpack <name>

################################################################################
# CMAKE CONFIGURATION                                                          #
################################################################################
cmake_minimum_required(3.0 FATAL_ERROR)

if(NOT ${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	message(FATAL_ERROR "GAME will only build for x86/64 systems.")
	return()
endif(NOT ${CMAKE_SIZEOF_VOID_P} EQUAL 8)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(WARNING "GAME prefers out-of-tree builds.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

list(INSERT "${CMAKE_MODULE_PATH}" 0 "${CMAKE_SOURCE_DIR}/CMake/Modules")

project(GAME)
enable_language(C)

include(GameSetVersion)
include(GameHandleBuildType)

configure_file(
	"${PROJECT_SOURCE_DIR}"/include/g_common.h.in
	"${PROJECT_BINARY_DIR}"/include/g_common.h
)

add_executable(game
	src/g_main.c
)

target_include_directories(game PUBLIC
	"${PROJECT_SOURCE_DIR}"/include
)

find_package(SDL2 REQUIRED)
target_include_directories(name ${SDL2_INCLUDE_DIRS})
target_link_libraries(name ${SDL2_LIBRARIES})

set(GAME_CREATOR "Ryan McClue")
set(GAME_BUG_REPORT_ADDRESS "<git-link>")
set(GAME_UNAME "GAME")
set(GAME_LNAME "game")
if(WINDOWS)
	set(GAME_BINARY_STRING "${GAME_LNAME}.exe")
else(WINDOWS)
	set(GAME_BINARY_STRING "${GAME_LNAME}")
endif(WINDOWS)
set(GAME_DESCRIPTION "Cross platform 2D SDL game.")
