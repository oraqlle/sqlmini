cmake_minimum_required(VERSION 3.21)

project(
    sqlmini
    VERSION 0.1.0
    DESCRIPTION "sqlite3 clone"
    LANGUAGES C
)

# ---- Declare library ----
add_library(
    sqlmini OBJECT
    src/sqlmini/compiler.c
    src/sqlmini/dbvm.c
    src/sqlmini/input.c
)

target_include_directories(
    sqlmini ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

# ---- Declare executable ----
add_executable(sqlmini_exe src/main.c)
add_executable(sqlmini::exe ALIAS sqlmini_exe)
set_property(TARGET sqlmini_exe PROPERTY OUTPUT_NAME sqlmini)
target_link_libraries(sqlmini_exe PRIVATE sqlmini)

# ---- Install rules ----
if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(cmake/install-rules.cmake)
endif()

