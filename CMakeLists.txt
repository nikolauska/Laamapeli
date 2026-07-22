cmake_minimum_required(VERSION 3.20)

project(Laamapeli LANGUAGES CXX)

set(USE_SANITIZER "" CACHE STRING
    "Enable sanitizers: Address, Undefined, Thread, Leak, Memory, or MemoryWithOrigins")
set(USE_STATIC_ANALYZER "" CACHE STRING
    "Enable static analyzers: clang-tidy, iwyu, and/or cppcheck")
set(CLANG_TIDY_ARGS "--checks=clang-analyzer-*" CACHE STRING
    "Additional clang-tidy arguments")
set(IWYU_ARGS "" CACHE STRING "Additional include-what-you-use arguments")
set(CPPCHECK_ARGS "" CACHE STRING "Additional cppcheck arguments")

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
    src/Audio.cpp
    src/Draw.cpp
    src/Events.cpp
    src/Ground.cpp
    src/GameState.cpp
    src/Settings.cpp
    src/Main.cpp
    src/Player.cpp
)

target_compile_features(Laamapeli PRIVATE cxx_std_23)
target_link_libraries(Laamapeli PRIVATE PkgConfig::ALLEGRO)

if(USE_SANITIZER)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        message(FATAL_ERROR "USE_SANITIZER requires Clang or GCC")
    endif()

    set(SANITIZER_FLAGS)
    foreach(SANITIZER IN LISTS USE_SANITIZER)
        if(SANITIZER STREQUAL "MemoryWithOrigins")
            if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
                message(FATAL_ERROR "MemoryWithOrigins requires Clang")
            endif()
            list(APPEND SANITIZER_FLAGS memory)
            target_compile_options(Laamapeli PRIVATE -fsanitize-memory-track-origins)
        elseif(SANITIZER MATCHES "^(Address|Undefined|Thread|Leak|Memory)$")
            string(TOLOWER "${SANITIZER}" SANITIZER_FLAG)
            list(APPEND SANITIZER_FLAGS "${SANITIZER_FLAG}")
        else()
            message(FATAL_ERROR "Unsupported sanitizer: ${SANITIZER}")
        endif()
    endforeach()

    list(JOIN SANITIZER_FLAGS "," SANITIZER_FLAGS)
    target_compile_options(Laamapeli PRIVATE
        "-fsanitize=${SANITIZER_FLAGS}"
        -fno-omit-frame-pointer
    )
    target_link_options(Laamapeli PRIVATE "-fsanitize=${SANITIZER_FLAGS}")
endif()

foreach(ANALYZER IN LISTS USE_STATIC_ANALYZER)
    if(ANALYZER STREQUAL "clang-tidy")
        find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy REQUIRED)
        set_property(TARGET Laamapeli PROPERTY CXX_CLANG_TIDY
            "${CLANG_TIDY_EXECUTABLE};${CLANG_TIDY_ARGS}")
    elseif(ANALYZER STREQUAL "iwyu")
        find_program(IWYU_EXECUTABLE NAMES include-what-you-use iwyu REQUIRED)
        set_property(TARGET Laamapeli PROPERTY CXX_INCLUDE_WHAT_YOU_USE
            "${IWYU_EXECUTABLE};${IWYU_ARGS}")
    elseif(ANALYZER STREQUAL "cppcheck")
        find_program(CPPCHECK_EXECUTABLE NAMES cppcheck REQUIRED)
        set_property(TARGET Laamapeli PROPERTY CXX_CPPCHECK
            "${CPPCHECK_EXECUTABLE};${CPPCHECK_ARGS}")
    else()
        message(FATAL_ERROR "Unsupported static analyzer: ${ANALYZER}")
    endif()
endforeach()

set(CPP_FORMAT_SOURCES
    src/Audio.cpp
    src/Audio.h
    src/Draw.cpp
    src/Draw.h
    src/Events.cpp
    src/GameState.cpp
    src/GameState.h
    src/Ground.cpp
    src/Ground.h
    src/Main.cpp
    src/Player.cpp
    src/Player.h
    src/Settings.cpp
    src/Settings.h
)

find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
find_program(CMAKE_FORMAT_EXECUTABLE NAMES cmake-format)

set(FORMAT_CHECK_COMMANDS)
set(FORMAT_FIX_COMMANDS)
if(CLANG_FORMAT_EXECUTABLE)
    list(APPEND FORMAT_CHECK_COMMANDS
        COMMAND "${CLANG_FORMAT_EXECUTABLE}" --dry-run --Werror
                ${CPP_FORMAT_SOURCES}
    )
    list(APPEND FORMAT_FIX_COMMANDS
        COMMAND "${CLANG_FORMAT_EXECUTABLE}" -i
                ${CPP_FORMAT_SOURCES}
    )
endif()
if(CMAKE_FORMAT_EXECUTABLE)
    list(APPEND FORMAT_CHECK_COMMANDS
        COMMAND "${CMAKE_FORMAT_EXECUTABLE}" --check
                CMakeLists.txt cmake/CopyIfMissing.cmake
    )
    list(APPEND FORMAT_FIX_COMMANDS
        COMMAND "${CMAKE_FORMAT_EXECUTABLE}" -i
                CMakeLists.txt cmake/CopyIfMissing.cmake
    )
endif()

if(FORMAT_CHECK_COMMANDS)
    add_custom_target(format
        ${FORMAT_CHECK_COMMANDS}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM
    )
    add_custom_target(fix-format
        ${FORMAT_FIX_COMMANDS}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        VERBATIM
    )
else()
    message(STATUS "clang-format and cmake-format not found; format targets disabled")
endif()

if(MSVC)
    target_compile_options(Laamapeli PRIVATE /W3)
endif()

add_custom_command(TARGET Laamapeli POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets/Default"
            "$<TARGET_FILE_DIR:Laamapeli>/Default"
    COMMAND "${CMAKE_COMMAND}"
            "-DSOURCE=${CMAKE_CURRENT_SOURCE_DIR}/assets/Settings.ini"
            "-DDESTINATION=$<TARGET_FILE_DIR:Laamapeli>/Settings.ini"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyIfMissing.cmake"
    VERBATIM
)
