cmake_minimum_required(VERSION 3.0)
project(Maxime)

add_definitions(
    # -DDEF_CIRCLE_WINS
    -DCONFIG_PLAYER_MANAGER_SDL
    -DCONFIG_SDLUI
)

set(SRC_FILES
    etape1/board.c
    etape1/player_manager_mock.c
    etape1/board_view_text.c
    etape1/main.c
    etape1/game.c
    etape1/tictactoe_errors.c
    etape2/player_manager_scanf.c
    etape3/board_view_sdl.c
    etape3/player_manager_sdl.c
    # test_tictactoe/main.c
    # test_tictactoe/test_CheckEndOfGame.c
)

include_directories(
    etape1
    etape2
    etape3
    # test_tictactoe
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_FILES})


target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)