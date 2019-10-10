add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    )

file (
    GLOB
    sources
    sources/*.cpp
    )

file (
    GLOB
    headers
    include/*.hpp
    )
add_executable(homenetctl ${sources})

target_compile_features(homenetctl
    PRIVATE cxx_variadic_templates)

target_include_directories(homenetctl PRIVATE include)

install(PROGRAMS homenetctl
    DESTINATION ${CMAKE_SOURCE_DIR})
