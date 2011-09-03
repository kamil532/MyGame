# Minimalna wersja cmake`a
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# Pliki zrodlowe dodane do projektu
set(SOURCES main.cpp			App.cpp			Renderer.cpp
	    Sprite.cpp			SpriteConfig.cpp	Level.cpp
	    SpriteGrid.cpp		Player.cpp		Aabb.cpp
	    Writer.cpp			Treasure.cpp    	Entity.cpp
	    ProgressBar.cpp		Menu.cpp
    ) 

# Ustawienia katalogow
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}) #jezeli: ${CMAKE_SOURCE_DIR} to binarki laduja w katalogu kodu
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}) 

#dolaczenie katalogow z kodem
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${SDL_INCLUDE_DIR})
link_directories(${CMAKE_SOURCE_ROOT}/lib)
link_directories(${LIBRARY_OUTPUT_PATH})

#Dolaczenie SDL`a
find_package(SDL REQUIRED)

#nazwa pliku wykonywalnego
add_executable(game ${SOURCES})

#flagi kompilatora
ADD_DEFINITIONS( "-Wall -ansi -pedantic")

############################################################################
 enable_testing()




