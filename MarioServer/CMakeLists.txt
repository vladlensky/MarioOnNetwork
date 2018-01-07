cmake_minimum_required(VERSION 3.3)
project(SI_Server)
link_libraries(pthread)
set(SOURCE_FILES
        game/Mario.h
        game/Enemy.c
        game/Mario.c
        game/Enemy.h
        game/GameState.c
        game/GameState.h
        game/JeuState.h
        network/net.c
        network/net.h
        network/packer.c
        network/packer.h
        network/packet.c
        network/packet.h
        main.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic ")
add_executable(SI_Server ${SOURCE_FILES})
add_custom_target(valgrind /usr/bin/valgrind ${PROJECT_BINARY_DIR}/SI_Server)
target_link_libraries(SI_Server -lSDLmain -lSDL -lSDL_image)