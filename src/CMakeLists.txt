add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
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

# Our only dependency is OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(homenetctl ${sources})

target_link_libraries(homenetctl ${OPENSSL_LIBRARIES})

target_compile_features(homenetctl
    PRIVATE cxx_variadic_templates)

target_include_directories(homenetctl PRIVATE include)
# install(PROGRAMS homenetctl  DESTINATION ${CMAKE_SOURCE_DIR})
