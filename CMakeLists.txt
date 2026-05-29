cmake_minimum_required(VERSION 3.16)
project(meu_jogo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

#SQLite
find_package(SQLite3 REQUIRED)

# raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

# box2d
FetchContent_Declare(
    box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG v3.1.0
)
FetchContent_MakeAvailable(box2d)

# googletest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_library(longprep_core
    src/Item/item.cpp
    src/Item/ItemList/itemlist.cpp
    src/Player/player.cpp
    src/Enemy/enemy.cpp
    src/Enemy/EnemyList/enemylist.cpp
    src/SaveManager/saveManager.cpp
)

target_include_directories(longprep_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Item
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Item/ItemList
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/EnemyList
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SaveManager
)

target_link_libraries(longprep_core
    raylib
    box2d
    SQLite::SQLite3
)

add_executable(meu_jogo
    src/main.cpp
)

target_link_libraries(meu_jogo
    longprep_core
)

enable_testing()

add_executable(tests
    tests/test_item.cpp
    tests/test_player.cpp
)

target_link_libraries(tests
    longprep_core
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)