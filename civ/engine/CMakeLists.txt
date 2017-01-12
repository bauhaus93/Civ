
set(engine_source_files
	Color.cpp
	Common.cpp
	Point.cpp
	Rect.cpp
)

if(${use_allegro})
	add_subdirectory(allegro)
elseif(${use_sdl})
	add_subdirectory(sdl)
endif()

message(STATUS ${engine_source_files})
