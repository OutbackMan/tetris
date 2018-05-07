if(DEFINED __GAME_BUILD_TYPES_CMAKE__)
  return()
endif(DEFINED __GAME_BUILD_TYPES_CMAKE__)
set(__GAME_BUILD_TYPES_CMAKE__ TRUE)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU|Clang")
	string(CONCAT 
		CMAKE_C_FLAGS 
		"-Wall -Wextra -Wpendantic -std=c99 -Wformat -Wshadow -Wcast-qual" 
		" -Wmissing-prototypes -msse2 -msse3 -march=native -ffat-lto-objects"
	)

	string(CONCAT 
		CMAKE_C_FLAGS_DEBUG 
		"-DGAME_BUILD_MODE_DEBUG -fsanitize=address -fsanitize=undefined -ggdb3" 
		" -g3 -O0"
	)

	string(CONCAT 
		CMAKE_C_FLAGS_MINSIZE_REL
		"-DGAME_BUILD_MODE_BUILD -Os -ffast-math -s -fmerge-all-constants"
		" -flto -fdata-sections -ffunction-sections -mtune=cpu-type"
		" -funsafe-loop-optimizations"
	)
	set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-s -Wl,--gc-sections")

	string(CONCAT 
		CMAKE_C_FLAGS_RELWITHDEBINFO 
		"-DGAME_BUILD_MODE_DEBUG -O3 -ffast-math -ggdb3 -g3 -fmerge-all-constants"
	)

	string(CONCAT 
		CMAKE_C_FLAGS_RELEASE
		"-DGAME_BUILD_MODE_RELEASE -O3 -ffast-math -fmerge-all-constants"
		" -flto -fdata-sections -ffunction-sections -mtune=cpu-type"
		" -funsafe-loop-optimizations"
	)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -Wl,--gc-sections")

	if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_C_FLAGS_DEBUG 
			"${CMAKE_C_FLAGS_DEBUG} -fsanitize=leak"
		)
	else("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_C_FLAGS_DEBUG 
			"${CMAKE_C_FLAGS_DEBUG} -fsanitize=dataflow -fsanitize=safe-stack"
		)
	endif("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	string(CONCAT 
		CMAKE_C_FLAGS_DEBUG 
		"/DGAME_BUILD_MODE_DEBUG" 
	)

	string(CONCAT 
		CMAKE_C_FLAGS_MINSIZE_REL
		"/DGAME_BUILD_MODE_RELEASE"
	)

	string(CONCAT 
		CMAKE_C_FLAGS_RELWITHDEBINFO 
		"/DGAME_BUILD_MODE_DEBUG"
	)

	string(CONCAT 
		CMAKE_C_FLAGS_RELEASE
		"/DGAME_BUILD_MODE_RELEASE"
	)
endif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")

if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif(NOT DEFINED CMAKE_BUILD_TYPE)
