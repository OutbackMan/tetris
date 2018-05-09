if(DEFINED __game_handle_build_type_cmake__)
  return()
endif(DEFINED __game_handle_build_type_cmake__)
set(__game_handle_build_type_cmake__ TRUE)

function(GameHandleBuildType target)
	target_compile_definitions(${target} PUBLIC "$<$<CONFIG:Debug>:GAME_BUILD_MODE_DEBUG>")
	target_compile_definitions(${target} PUBLIC "$<$<CONFIG:Release>:GAME_BULD_MODE_RELEASE>")
	target_compile_definitions(${target} PUBLIC "$<$<CONFIG:MinSizeRel>:GAME_BUILD_MODE_RELEASE>")
	target_compile_definitions(${target} PUBLIC "$<$<CONFIG:RelWithDebInfo>:GAME_BUILD_MODE_DEBUG>")

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

		target_compile_options(${target} PUBLIC "$<$<CONFIG:Debug>:${GCC_CLANG_DEBUG_OPTIONS}>")

		target_compile_options(${target} PUBLIC "$<$<CONFIG:Release>:${GCC_CLANG_RELEASE_OPTIONS}>")
		set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -Wl,--gc-sections" PARENT_SCOPE)

		target_compile_options(${target} PUBLIC "$<$<CONFIG:MinSizeRel>:${GCC_CLANG_MINSIZEREL_OPTIONS}>")
		set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "-s -Wl,--gc-sections" PARENT_SCOPE)

		target_compile_options(${target} PUBLIC "$<$<CONFIG:RelWithDebInfo>:${GCC_CLANG_RELWITHDEBINFO_OPTIONS}>")
	endif(${CMAKE_C_COMPILER_ID} STREQUAL "GNU|Clang")

	if(NOT DEFINED CMAKE_BUILD_TYPE)
	  set(CMAKE_BUILD_TYPE "Debug" PARENT_SCOPE)
	endif(NOT DEFINED CMAKE_BUILD_TYPE)
endfunction(GameHandleBuildType)

