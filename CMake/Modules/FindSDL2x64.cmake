if(DEFINED __find_sdlx64_cmake__)
  return()
endif(DEFINED __find_sdlx64_cmake__)
set(__find_sdlx64_cmake__ TRUE)

set(SDL2x64_SEARCH_PATHS
	~/Library/Frameworks # dynamic shared object file with headers etc.
	/Library/Frameworks
	/usr/local # linux structure
	/usr
	/opt/local # self contained structure
	/opt
)

find_path(SDL2x64_INCLUDE_DIR SDL.h
	HINTS ENV SDL2_DIR
	PATH_SUFFIXES include/SDL2 include
	PATHS ${SDL2_SEARCH_PATHS}
)

find_library(SDL2x64_LIBRARY_TEMP
	NAMES SDL2
	HINTS ENV SDL2_LIB
	PATH_SUFFIXES lib64 lib/x64 lib
	PATHS ${SDL2_SEARCH_PATHS}
)

if(NOT ${SDL2x64_INCLUDE_DIR} MATCHES ".framework")
	find_library(SDL2x64MAIN_LIBRARY
		NAMES SDL2main
		HINTS ENV SDL2x64DIR
		PATH_SUFFIXES ${PATH_SUFFIXES} # HERE
		PATHS ${SDL2x64_SEARCH_PATHS}
	)
endif(NOT ${SDL2x64_INCLUDE_DIR} MATCHES ".framework")

if(NOT APPLE)
	find_package(Threads)
endif(NOT APPLE)

if(SDL2x64_LIBRARY_TEMP)
	if(SDL2x64MAIN_LIBRARY)
		set(SDL2x64_LIBRARY_TEMP ${SDL2x64MAIN_LIBRARY} ${SDL2x64_LIBRARY_TEMP})
	endif(SDL2x64MAIN_LIBRARY)

	if(APPLE)
		SET(SDL2x64_LIBRARY_TEMP ${SDL2x64_LIBRARY_TEMP} "-framework Cocoa")
	endif(APPLE)
	if(NOT APPLE)
		set(SDL2x64_LIBRARY_TEMP ${SDL2x64_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
	endif(NOT APPLE)

	# Set the final string here so the GUI reflects the final state.
	set(SDL2x64_LIBRARY ${SDL2x64_LIBRARY_TEMP} CACHE STRING "Where the SDL2 Library can be found")
	# Set the temp variable to INTERNAL so it is not seen in the CMake GUI
	set(SDL2x64_LIBRARY_TEMP "${SDL2x64_LIBRARY_TEMP}" CACHE INTERNAL "")
endif(SDL2x64_LIBRARY_TEMP)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2x64 REQUIRED_VARS SDL2x64_LIBRARY SDL2x64_INCLUDE_DIR)
