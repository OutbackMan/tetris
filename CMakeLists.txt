#@ Author       "Ryan McClue" <mcclue.ryan@gmail.com>
#@ Description  Cross platform 2D SDL game.
#@ Usage: 
#@ GENERAL:
#@	1. mkdir build/ && cd build/ && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .
#@	2. ctest [-R <test-suite>]
#@	3. cpack [-C <build-type>]

# sdl ios/android cmake repositories, sdl_gpu, dinomage games
# Have to build from source for android and ios builds
# iOS: xcodebuild -target "${PROJECT_NAME}" -sdk "${TARGET_SDK}" -configuration Release (.app)
# /usr/bin/xcrun -sdk iphoneos PackageApplication -v "${RELEASE_BUILDDIR}/${APPLICATION_NAME}.app" -o "${BUILD_HISTORY_DIR}/${APPLICATION_NAME}.ipa" --sign "${DEVELOPER_NAME}" --embed "${PROVISONING_PROFILE}” (.ipa)

# ANDROID: (for testing --> droid@screen)
# cp -r SDL2/android-project game/platforms/android
# ln -s SDL2-2.0.3 SDL2 && ln -s SDL2-2.0.3_ttf SDL2_ttf
# src/org/libsdl/app/SDLActivity.java uncomment System.loadLibrary("SDL2_ttf"). this calls main via JNI. adb to install
# REQUIREMENTS --> JDK (comes with JRE), android SDK and NDK, gradle
# git clone https://github.com/spurious/SDL-mirror (git clone https://github.com/aduros/SDL_image)
# OR PERHAPS DOWNLOAD .tar.gz and .zip files
# cd android (gradle files)
# ./gradlew assembleDebug (perhaps use ant instead)
# ./gradlew installDebug
# SDLActivity.java
# put our source files in SDL-mirror/android-project/jni/src/

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

set(_game_utils_sources
	src/utils/log.c
	src/utils/status.c
	src/utils/args.c
	src/utils/math.c
	src/core/game.c
)

set(_game_sources
	src/main.c
	${_game_utils_sources}
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

set(G_CREATOR "Ryan McClue")
set(G_VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
set(G_BUG_REPORT_ADDRESS "<git-link>")
set(G_NAME "Game")
set(G_LNAME "game")
set(G_UNAME "GAME")
if(WINDOWS)
	set(G_BINARY_STRING ${GAME_LNAME}.exe)
else(WINDOWS)
	set(G_BINARY_STRING ${GAME_LNAME})
endif(WINDOWS)
set(G_DESCRIPTION "Cross platform 2D SDL game.")

configure_file(
	${CMAKE_SOURCE_DIR}/include/common.h.in
	${CMAKE_SOURCE_DIR}/include/common.h
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
add_executable(game_test_driver ${_game_sources} tests/test-helpers.c)
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
set(CPACK_PACKAGE_NAME ${G_LNAME})
set(CPACK_PACKAGE_VENDOR ${G_CREATOR})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${G_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${G_VERSION})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${G_LNAME}-${G_VERSION}")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/images/icon.ico")
set(CPACK_PACKAGE_EXECUTABLES ${G_LNAME} ${G_NAME})
include(CPack)
