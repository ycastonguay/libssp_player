cmake_minimum_required(VERSION 2.8.4)
project(org_sessionsapp_player)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    bass/ios/bass_fx.h
    bass/bass.h
    bass/bass_fx.h
    bass/bassenc.h
    bass/bassflac.h
    bass/bassmidi.h
    bass/bassmix.h
    bass/basswv.h
    player/main.c
    player/ssp_callbacks.h
    player/ssp_errors.h
    player/ssp_player.c
    player/ssp_player.h
    player/ssp_playlist.c
    player/ssp_structs.h
    player-ios-library/player_ios_library.h)

add_executable(org_sessionsapp_player ${SOURCE_FILES})