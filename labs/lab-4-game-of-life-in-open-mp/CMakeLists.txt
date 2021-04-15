cmake_minimum_required(VERSION 3.19)
project(lab_4_game_of_life_in_open_mp C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_4_game_of_life_in_open_mp sequential_version/config.c sequential_version/game.c sequential_version/main.c sequential_version/mem.c)