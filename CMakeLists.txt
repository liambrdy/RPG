cmake_minimum_required(VERSION 3.16)

project(RPG CXX)
include(cmake/StandardProjectSettings.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

add_library(project_warnings INTERFACE)

include(cmake/Cache.cmake)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/StaticAnalyzers.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)

option(ENABLE_PCH "Enable Precompiled headers" OFF)
if (${ENABLE_PCH})
    target_precompile_headers(project_options INTERFACE <vector> <string> <utility> <map>)
endif ()

set(CONAN_EXTRA_REQUIRES "imgui-sfml/2.1@bincrafters/stable")
set(CONAN_EXTRA_OPTIONS "")

include(cmake/Conan.cmake)
run_conan()

if (${ENABLE_TESTING})
    enable_testing()
    message("Building tests")
    add_subdirectory(tests)
endif ()

add_subdirectory(src)
