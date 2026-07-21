cmake_minimum_required(VERSION 3.20)

project(Laamapeli LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO REQUIRED IMPORTED_TARGET
    allegro-5>=5.2.6
    allegro_main-5>=5.2.6
    allegro_image-5>=5.2.6
    allegro_font-5>=5.2.6
    allegro_ttf-5>=5.2.6
    allegro_audio-5>=5.2.6
    allegro_acodec-5>=5.2.6
    allegro_dialog-5>=5.2.6
)

add_executable(Laamapeli
    Laamapeli/Audio.cpp
    Laamapeli/Draw.cpp
    Laamapeli/Events.cpp
    Laamapeli/Ground.cpp
    Laamapeli/Initialize_Destroy.cpp
    Laamapeli/Ini_other.cpp
    Laamapeli/Main.cpp
    Laamapeli/Player.cpp
    Laamapeli/Timers.cpp
)

target_compile_features(Laamapeli PRIVATE cxx_std_11)
target_link_libraries(Laamapeli PRIVATE PkgConfig::ALLEGRO)

if(MSVC)
    target_compile_options(Laamapeli PRIVATE /W3)
endif()

add_custom_command(TARGET Laamapeli POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Laamapeli/Default"
            "$<TARGET_FILE_DIR:Laamapeli>/Default"
    COMMAND "${CMAKE_COMMAND}"
            "-DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/Laamapeli/Settings.ini"
            "-DDESTINATION=$<TARGET_FILE_DIR:Laamapeli>/Settings.ini"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyIfMissing.cmake"
    VERBATIM
)
