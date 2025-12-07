# 指定所需的最低 CMake 版本
cmake_minimum_required(VERSION 3.10.0)
# 定义项目名称、版本和使用的编程语言
project(asd VERSION 0.1.0 LANGUAGES C CXX)

# 设置 C++ 标准版本为 C++17
set(CMAKE_CXX_STANDARD 17)
# 要求必须使用 C++17 标准
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 根据编译器类型设置不同的编译选项
if (MSVC)
    # 对于 MSVC 编译器，设置警告级别为 W4
    add_compile_options(/W4)
    # 设置目标为 Windows 控制台应用程序
    set_target_properties(${TARGET} PROPERTIES WIN32_EXECUTABLE TRUE)
else()  
    # 对于其他编译器，启用额外的警告选项
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# 设置目标名称，包含项目名称和系统名称
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})


# 查找所需的 SDL3 相关库
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)

# 添加可执行文件，指定所有源文件
add_executable(${TARGET}    src/main.cpp  
                            src/Game.cpp
                            src/SceneMenu.cpp
                            src/SceneGame.cpp
                            src/Button.cpp
                            src/ResourcesManager.cpp
                            src/Animation.cpp
                            src/Player.cpp
                            src/Enemy.cpp)

# 链接所需的库文件
target_link_libraries(${TARGET}
                        ${SDL3_LIBRARIES}
                        SDL3_image::SDL3_image
                        SDL3_mixer::SDL3_mixer
                        SDL3_ttf::SDL3_ttf)

