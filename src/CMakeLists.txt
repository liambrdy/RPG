set(SOURCES Game.cpp Window.cpp Events.cpp Config.cpp ResourceManager.cpp)
set(HEADERS Scene.h Game.h Window.h Events.h Config.h ResourceManager.h)

add_library(RPG_common OBJECT ${SOURCES} ${HEADERS})
target_include_directories(RPG_common INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(RPG_common project_options project_warnings CONAN_PKG::spdlog CONAN_PKG::sfml)

add_executable(RPG main.cpp)
target_link_libraries(RPG RPG_common)
