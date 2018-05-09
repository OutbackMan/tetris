set(SDL2_SEARCH_PATHS
	~/Library/Frameworks # dynamic shared object file with headers etc.
	/Library/Frameworks
	/usr/local # linux structure
	/usr
	/opt/local # self contained structure
	/opt
)

find_path(SDL2_INCLUDE_DIR SDL.h
	HINTS ENV SDL2_DIR
	PATH_SUFFIXES include/SDL2 include
	PATHS ${SDL2_SEARCH_PATHS}
)

find_library(SDL2_LIBRARY_TEMP
	NAMES SDL2
	HINTS ENV SDL2DIR
	PATH_SUFFIXES lib64 lib/x64 lib
	PATHS ${SDL2_SEARCH_PATHS}
)

if(NOT ${SDL2_INCLUDE_DIR} MATCHES ".framework")
	# Non-OS X framework versions expect you to also dynamically link to
	# SDL2main. This is mainly for Windows and OS X. Other (Unix) platforms
	# seem to provide SDL2main for compatibility even though they don't
	# necessarily need it.
	find_library(SDL2MAIN_LIBRARY
		NAMES SDL2main
		HINTS
		$ENV{SDL2DIR}
		PATH_SUFFIXES ${PATH_SUFFIXES}
		PATHS ${SDL2_SEARCH_PATHS}
	)
endif(NOT ${SDL2_INCLUDE_DIR} MATCHES ".framework")

# SDL2 may require threads on your system.
# The Apple build may not need an explicit flag because one of the
# frameworks may already provide it.
# But for non-OSX systems, I will use the CMake Threads package.
if(NOT APPLE)
	find_package(Threads)
endif(NOT APPLE)

if(SDL2_LIBRARY_TEMP)
	if(SDL2MAIN_LIBRARY)
		set(SDL2_LIBRARY_TEMP ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY_TEMP})
	endif(SDL2MAIN_LIBRARY)

	# For OS X, SDL2 uses Cocoa as a backend so it must link to Cocoa.
	# CMake doesn't display the -framework Cocoa string in the UI even
	# though it actually is there if I modify a pre-used variable.
	# I think it has something to do with the CACHE STRING.
	# So I use a temporary variable until the end so I can set the
	# "real" variable in one-shot.
	if(APPLE)
		SET(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} "-framework Cocoa")
	endif(APPLE)

	# For threads, as mentioned Apple doesn't need this.
	# In fact, there seems to be a problem if I used the Threads package
	# and try using this line, so I'm just skipping it entirely for OS X.
	if(NOT APPLE)
		set(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
	endif(NOT APPLE)

	# Set the final string here so the GUI reflects the final state.
	set(SDL2_LIBRARY ${SDL2_LIBRARY_TEMP} CACHE STRING "Where the SDL2 Library can be found")
	# Set the temp variable to INTERNAL so it is not seen in the CMake GUI
	set(SDL2_LIBRARY_TEMP "${SDL2_LIBRARY_TEMP}" CACHE INTERNAL "")
endif(SDL2_LIBRARY_TEMP)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)
