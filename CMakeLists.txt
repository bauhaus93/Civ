cmake_minimum_required(VERSION 3.4.3)
project(Civ)


macro(add_sources)
	file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")

	foreach(_src ${ARGN})
		if(_relPath)
			set_property(GLOBAL APPEND PROPERTY SRC_LIST "${_relPath}/${_src}")
		else()
			set_property(GLOBAL APPEND PROPERTY SRC_LIST "${_src}")
		endif()
	endforeach()
endmacro()

set(GCC_COMPILE_FLAGS "-std=c++14 -Wall")
set(GCC_LINK_FLAGS "-std=c++14 -Wall")

#set(use_allegro 1)
set(use_sdl 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COMPILE_FLAGS}")

include_directories(/usr/include)
include_directories(civ)

add_subdirectory(civ)

get_property(SOURCES GLOBAL PROPERTY SRC_LIST)
#string(REPLACE ";" " " SOURCES "${_srcs}")

if(${use_allegro})
	find_library(ALLEGRO_LIB NAMES allegro PATHS /usr/lib/ /usr/local/lib)
	find_library(ALLEGRO_PRIMITIVES_LIB NAMES allegro_primitives PATHS /usr/lib/ /usr/local/lib)
	find_library(ALLEGRO_IMAGE_LIB NAMES allegro_image PATHS /usr/lib /usr/local/lib)
	find_library(ALLEGRO_MAIN_LIB NAMES allegro_main PATHS /usr/lib /usr/local/lib)
endif()

message(STATUS "SOURCES: ${SOURCES}")

add_executable(civ2 ${SOURCES})

if(${use_allegro})
	target_link_libraries(civ2 ${ALLEGRO_LIB})
	target_link_libraries(civ2 ${ALLEGRO_PRIMITIVES_LIB})
	target_link_libraries(civ2 ${ALLEGRO_IMAGE_LIB})
	target_link_libraries(civ2 ${ALLEGRO_MAIN_LIB})
endif()
