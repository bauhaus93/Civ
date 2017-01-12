cmake_minimum_required(VERSION 3.4.3)
project(Civ)


set(civ_source_files
	Event.cpp
	FPSHandler.cpp
	Game.cpp
	Log.cpp
	Main.cpp
)
add_subdirectory(common)
add_subdirectory(engine)
#add_subdirectory(exception)
#add_subdirectory(map)
#add_subdirectory(tile)

