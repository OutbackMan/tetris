if(DEFINED __handle_build_type_cmake__)
  return()
endif(DEFINED __handle_build_type_cmake__)
set(__handle_build_type_cmake__ TRUE)

function(HandleBuildType target)
	if(NOT CMAKE_BUILD_TYPE)
	  set(CMAKE_BUILD_TYPE "Debug" PARENT_SCOPE)
	endif(NOT CMAKE_BUILD_TYPE)

	target_compile_definitions(${target} PUBLIC $<$<CONFIG:Debug>:GAME_BUILD_MODE_DEBUG>)
	target_compile_definitions(${target} PUBLIC $<$<CONFIG:Release>:GAME_BUILD_MODE_RELEASE>)
	target_compile_definitions(${target} PUBLIC $<$<CONFIG:MinSizeRel>:GAME_BUILD_MODE_RELEASE>)
	target_compile_definitions(${target} PUBLIC $<$<CONFIG:RelWithDebInfo>:GAME_BUILD_MODE_DEBUG>)

	if(${CMAKE_C_COMPILER_ID} MATCHES "GNU|Clang")
		string(CONCAT
			GCC_CLANG_COMMON_OPTIONS
			"-Wall -Wextra -Wpedantic -std=c99 -Wformat -Wshadow -Wcast-qual" 
			" -Wmissing-prototypes -msse2 -msse3 -march=native"
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
			" -ffunction-sections -mtune=native -funsafe-loop-optimizations"
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
			" -flto -fdata-sections -ffunction-sections -mtune=native"
		)

		if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
			string(CONCAT GCC_CLANG_DEBUG_OPTIONS ${GCC_CLANG_DEBUG_OPTIONS} " -fsanitize=leak")
			string(CONCAT GCC_CLANG_RELEASE_OPTIONS ${GCC_CLANG_RELEASE_OPTIONS} " -funsafe-loop-optimizations")
		else(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
			string(CONCAT GCC_CLANG_DEBUG_OPTIONS ${GCC_CLANG_DEBUG_OPTIONS} " -fsanitize=dataflow -fsanitize=safe-stack")
		endif(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")

		string(REPLACE " " ";" GCC_CLANG_DEBUG_OPTIONS ${GCC_CLANG_DEBUG_OPTIONS})
		string(REPLACE " " ";" GCC_CLANG_RELEASE_OPTIONS ${GCC_CLANG_RELEASE_OPTIONS})
		string(REPLACE " " ";" GCC_CLANG_MINSIZEREL_OPTIONS ${GCC_CLANG_MINSIZEREL_OPTIONS})
		string(REPLACE " " ";" GCC_CLANG_RELWITHDEBINFO_OPTIONS ${GCC_CLANG_RELWITHDEBINFO_OPTIONS})

		target_compile_options(${target} PUBLIC $<$<CONFIG:Debug>:${GCC_CLANG_DEBUG_OPTIONS}>)
		target_link_libraries(${target} PUBLIC $<$<CONFIG:Debug>:"asan">)
		target_link_libraries(${target} PUBLIC $<$<CONFIG:Debug>:"ubsan">)

		target_compile_options(${target} PUBLIC $<$<CONFIG:Release>:${GCC_CLANG_RELEASE_OPTIONS}>)

		target_compile_options(${target} PUBLIC $<$<CONFIG:MinSizeRel>:${GCC_CLANG_MINSIZEREL_OPTIONS}>)

		target_compile_options(${target} PUBLIC $<$<CONFIG:RelWithDebInfo>:${GCC_CLANG_RELWITHDEBINFO_OPTIONS}>)
	elseif(${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
		target_compile_definitions(${target} PUBLIC _CRT_SECURE_NO_WARNINGS)
	else(${CMAKE_C_COMPILER_ID} MATCHES "GNU|Clang")
		message(FATAL_ERROR "[HandleBuildType] Your compiler is not either of the supported gcc, clang or msvc")
	endif(${CMAKE_C_COMPILER_ID} MATCHES "GNU|Clang")
endfunction(HandleBuildType)
