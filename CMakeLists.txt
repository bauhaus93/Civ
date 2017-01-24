cmake_minimum_required(VERSION 3.4.3)
project(Civ CXX)

macro(add_sources)
	file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")

	foreach(_src ${ARGN})


		if(_relPath)
			if(ENABLE_SDL AND ${_relPath} MATCHES "/sdl$")
				set_property(TARGET civ_sdl APPEND PROPERTY SRC_LIST "${_relPath}/${_src}")
			elseif(ENABLE_ALLEGRO AND ${_relPath} MATCHES "/allegro$")
				set_property(TARGET civ_allegro APPEND PROPERTY SRC_LIST "${_relPath}/${_src}")
			else()

				if(ENABLE_SDL)
					set_property(TARGET civ_sdl APPEND PROPERTY SRC_LIST "${_relPath}/${_src}")
				endif()

				if(ENABLE_ALLEGRO)
					set_property(TARGET civ_allegro APPEND PROPERTY SRC_LIST "${_relPath}/${_src}")
				endif()

			endif()

		else()
			set_property(GLOBAL APPEND PROPERTY SRC_LIST "${_src}")
		endif()
	endforeach()
endmacro()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(COMPILE_FLAGS "-std=c++14 -Wall -fmax-errors=1")
	set(LINK_FLAGS "-std=c++14 -Wall -fmax-errors=1")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(COMPILE_FLAGS "-std=c++14 -Wall -ferror-limit=1")
		set(LINK_FLAGS "--std=c++14 -Wall -ferror-limit=1")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(COMPILE_FLAGS "/W4")
	#set(LINK_FLAGS "/NODEFAULTLIB:msvcrtd.lib")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

option(ENABLE_ALLEGRO "Enable building with allegro" ON)
option(ENABLE_SDL "Enable building with sdl2" ON)

if(ENABLE_ALLEGRO)
	add_executable(civ_allegro "")
endif()

if(ENABLE_SDL)
	add_executable(civ_sdl "")
endif()

include_directories(/usr/include)
include_directories(src)

add_subdirectory(src)

file(COPY src/bmp DESTINATION .)

if(ENABLE_ALLEGRO)
	target_compile_definitions(civ_allegro PRIVATE ENGINE_ALLEGRO)
	if(WIN32)
		target_include_directories(civ_allegro PRIVATE C:/allegro/include)
	endif()

	get_property(SRC_ALLEGRO TARGET civ_allegro PROPERTY SRC_LIST)
	target_sources(civ_allegro PRIVATE ${SRC_ALLEGRO} PRIVATE ${SRC_ALLEGRO})

	find_library(ALLEGRO_LIB NAMES allegro PATHS /usr/lib/ /usr/local/lib C:/allegro/lib)
	find_library(ALLEGRO_PRIMITIVES_LIB NAMES allegro_primitives PATHS /usr/lib/ /usr/local/lib C:/allegro/lib)
	find_library(ALLEGRO_IMAGE_LIB NAMES allegro_image PATHS /usr/lib /usr/local/lib C:/allegro/lib)
	find_library(ALLEGRO_MAIN_LIB NAMES allegro_main PATHS /usr/lib /usr/local/lib C:/allegro/lib)

	target_link_libraries(civ_allegro ${ALLEGRO_LIB})
	target_link_libraries(civ_allegro ${ALLEGRO_PRIMITIVES_LIB})
	target_link_libraries(civ_allegro ${ALLEGRO_IMAGE_LIB})
	target_link_libraries(civ_allegro ${ALLEGRO_MAIN_LIB})
endif()

if(ENABLE_SDL)
	target_compile_definitions(civ_sdl PRIVATE ENGINE_SDL)
	if(WIN32)
		target_include_directories(civ_sdl PRIVATE C:/SDL2/include)
	endif()

	get_property(SRC_SDL TARGET civ_sdl PROPERTY SRC_LIST)
	target_sources(civ_sdl PRIVATE ${SRC_SDL})

	find_library(SDL_LIB NAMES SDL2 PATHS /usr/lib/ /usr/local/lib C:/SDL2/lib)
	find_library(SDL_MAIN_LIB NAMES SDL2main PATHS /usr/lib/ /usr/local/lib C:/SDL2/lib)

	target_link_libraries(civ_sdl ${SDL_LIB})
	target_link_libraries(civ_sdl ${SDL_MAIN_LIB})
endif()
