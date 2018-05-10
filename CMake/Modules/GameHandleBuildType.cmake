if(DEFINED __game_handle_build_type_cmake__)
  return()
endif(DEFINED __game_handle_build_type_cmake__)
set(__game_handle_build_type_cmake__ TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

target_compile_definitions(game PUBLIC $<$<CONFIG:Debug>:GAME_BUILD_MODE_DEBUG>)
target_compile_definitions(game PUBLIC $<$<CONFIG:Release>:GAME_BUILD_MODE_RELEASE>)
target_compile_definitions(game PUBLIC $<$<CONFIG:MinSizeRel>:GAME_BUILD_MODE_RELEASE>)
target_compile_definitions(game PUBLIC $<$<CONFIG:RelWithDebInfo>:GAME_BUILD_MODE_DEBUG>)

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU|Clang")
	string(CONCAT
		GCC_CLANG_COMMON_OPTIONS
		"-Wall -Wextra -Wpendantic -std=c99 -Wformat -Wshadow -Wcast-qual" 
		" -Wmissing-prototypes -msse2 -msse3 -march=native -ffat-lto-objects"
	)

	string(CONCAT 
		GCC_CLANG_DEBUG_OPTIONS
		${GCC_CLANG_COMMON_OPTIONS}
		" -fsanitize=address -fsanitize=undefined -ggdb3 -g3 -O0"
	)

	string(CONCAT 
		GCC_CLANG_MINSIZEREL_OPTIONS
		${GCC_CLANG_COMMON_OPTIONS}
		" -Os -ffast-math -s -fmerge-all-constants -flto -fdata-sections"
		" -ffunction-sections -mtune=cpu-type -funsafe-loop-optimizations"
	)
	string(CONCAT 
		GCC_CLANG_RELWITHDEBINFO_OPTIONS
		${GCC_CLANG_COMMON_OPTIONS}
		" -O3 -ffast-math -ggdb3 -g3 -fmerge-all-constants"
	)

	string(CONCAT 
		GCC_CLANG_RELEASE_OPTIONS
		${GCC_CLANG_COMMON_OPTIONS}
		" -O3 -ffast-math -fmerge-all-constants"
		" -flto -fdata-sections -ffunction-sections -mtune=cpu-type"
		" -funsafe-loop-optimizations"
	)

	if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
		string(CONCAT GCC_CLANG_DEBUG_OPTIONS " -fsanitize=leak")
	else(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
		string(CONCAT GCC_CLANG_DEBUG_OPTIONS " -fsanitize=dataflow -fsanitize=safe-stack")
	endif(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")

	target_compile_options(game PUBLIC $<$<CONFIG:Debug>:${GCC_CLANG_DEBUG_OPTIONS}>)

	target_compile_options(game PUBLIC $<$<CONFIG:Release>:${GCC_CLANG_RELEASE_OPTIONS}>)
	target_link_libraries(game PUBLIC $<$<CONFIG:Release>:-s -Wl,--gc-sections>)

	target_compile_options(game PUBLIC $<$<CONFIG:MinSizeRel>:${GCC_CLANG_MINSIZEREL_OPTIONS}>)
	target_link_libraries(game PUBLIC $<$<CONFIG:Release>:-s -Wl,--gc-sections>)

	target_compile_options(game PUBLIC $<$<CONFIG:RelWithDebInfo>:${GCC_CLANG_RELWITHDEBINFO_OPTIONS}>)
endif(${CMAKE_C_COMPILER_ID} STREQUAL "GNU|Clang")
