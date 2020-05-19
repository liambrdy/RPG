add_executable(RPG main.cpp)

target_link_libraries(
    RPG PRIVATE project_options project_warnings CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::sfml
                CONAN_PKG::imgui-sfml
)
