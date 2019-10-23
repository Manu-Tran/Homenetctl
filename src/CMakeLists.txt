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
    include/*.h
    )

# Our only dependency is POCO
# find_library(Poco_LIBRARIES NAMES PocoFoundationmt PocoNetmt PATH_SUFFIXES ${POCO_DIR}/lib)
find_package(Poco REQUIRED Foundation Net Crypto NetSSL)

add_executable(homenetctl ${sources})

target_link_libraries(homenetctl PUBLIC Poco::NetSSL Poco::Foundation Poco::Crypto Poco::Net)

target_compile_features(homenetctl
    PRIVATE cxx_variadic_templates)

target_include_directories(homenetctl PRIVATE include)
# install(PROGRAMS homenetctl  DESTINATION ${CMAKE_SOURCE_DIR})
