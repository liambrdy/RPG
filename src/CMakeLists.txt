set(SOURCES scenes/Game.cpp renderer/Window.cpp core/Events.cpp core/Config.cpp
            renderer/ResourceManager.cpp
        ecs/ECS.cpp)
set(HEADERS
    scenes/Scene.h
    scenes/Game.h
    renderer/Window.h
    core/Events.h
    core/Config.h
    renderer/ResourceManager.h
    ecs/EntityManager.h
    ecs/ComponentArray.h
    ecs/ComponentManager.h
    ecs/SystemManager.h
    ecs/ECS.h
)

add_library(RPG_common OBJECT ${SOURCES} ${HEADERS})
target_include_directories(RPG_common PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(RPG_common project_options project_warnings CONAN_PKG::spdlog CONAN_PKG::sfml)

add_executable(RPG main.cpp)
target_link_libraries(RPG RPG_common)
