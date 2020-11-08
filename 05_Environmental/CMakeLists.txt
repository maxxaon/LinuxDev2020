cmake_minimum_required(VERSION 3.1)

project(window)

set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

find_library(PCRE_LIBRARY pcre2-8)

if(without_UTF)
  add_definitions(-DWITHOUT_UTF)
endif()

add_executable(window window.c pcre_prog.c)

target_link_libraries(window ${CURSES_LIBRARIES} ${PCRE_LIBRARY})

add_custom_target(allclean)

set(
    GENERATS
    window
    CMakeCache.txt
    CMakeFiles
    *.cmake
    Makefile
)

add_custom_command(
    COMMAND rm
    ARGS -rf ${GENERATS}
    TARGET allclean
)