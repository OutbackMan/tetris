#@ Author       "Ryan McClue" <mcclue.ryan@gmail.com>
#@ Description  Cross platform 2D SDL game.
#@ Usage: 
#@ GENERAL:
#@	1. mkdir build/ && cd build/ && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .
#@	2. ctest [-R <test-suite>]
#@	3. cpack [-C <build-type>]

################################################################################
# CMAKE CONFIGURATION                                                          #
################################################################################
cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

if(NOT ${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	message(FATAL_ERROR "[GAME] Will only build for x86/64 systems.")
	return()
endif(NOT ${CMAKE_SIZEOF_VOID_P} EQUAL 8)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "[GAME] Require out-of-tree builds.")
	return()
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

project(GAME)
enable_language(C)

include(HandleVersion)
HandleVersion()

set(_game_sources
	src/g_main.c
	src/utils/g_log.c
)

add_executable(game
	${_game_sources}
)

include(HandleBuildType)
HandleBuildType(game)

target_include_directories(game PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

find_package(SDL2x64 REQUIRED)
target_include_directories(game PUBLIC ${SDL2x64_INCLUDE_DIRS})
target_link_libraries(game ${SDL2x64_LIBRARIES})

set(GAME_CREATOR "Ryan McClue")
set(GAME_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
set(GAME_BUG_REPORT_ADDRESS "<git-link>")
set(GAME_NAME "Game")
set(GAME_LNAME "game")
set(GAME_UNAME "GAME")
if(WINDOWS)
	set(GAME_BINARY_STRING ${GAME_LNAME}.exe)
else(WINDOWS)
	set(GAME_BINARY_STRING ${GAME_LNAME})
endif(WINDOWS)
set(GAME_DESCRIPTION "Cross platform 2D SDL game.")

configure_file(
	${CMAKE_SOURCE_DIR}/include/g_common.h.in
	${CMAKE_SOURCE_DIR}/include/g_common.h
)

################################################################################
# CTEST CONFIGURATION                                                          #
################################################################################

enable_testing()

set(_game_test_suites
	example
)

set(example_tests "test_a" "test_b")

foreach(game_test_suite ${_game_test_suites})
	list(APPEND _game_test_suite_sources tests/${game_test_suite}TestSuite.c)
endforeach(game_test_suite)

create_test_sourcelist(_game_sources game_test_driver.c ${_game_test_suite_sources})
add_executable(game_test_driver ${_game_sources} tests/g_test-helpers.c)
target_link_libraries(game_test_driver ${SDL2x64_LIBRARIES})

foreach(game_test_suite ${_game_test_suites})
	foreach(game_test ${${game_test_suite}_tests})
		add_test(NAME ${game_test_suite}_${game_test}
			COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/game_test_driver tests/${game_test_suite}TestSuite ${game_test_suite}_${game_test}
		)
	endforeach(game_test)
endforeach(game_test_suite)

################################################################################
# CPACK CONFIGURATION                                                          #
################################################################################
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME ${GAME_LNAME})
set(CPACK_PACKAGE_VENDOR ${GAME_CREATOR})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${GAME_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${GAME_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${GAME_LNAME}-${GAME_VERSION}")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/images/icon.ico")
set(CPACK_PACKAGE_EXECUTABLES ${GAME_LNAME} ${GAME_NAME})
include(CPack)
