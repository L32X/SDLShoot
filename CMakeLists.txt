cmake_minimum_required(VERSION 4.0)
project(SDLShooter VERSION 0.1.0 LANGUAGES C CXX)

# 设置 cpp 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# 设置编译选项
add_compile_options(-Wall -Wextra -Wpedantic)

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# 查找 SDL2 包
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
# message(STATUS "SDL2 targets: ${SDL2_LIBRARIES}")

# 设置输出运行文件相关平台名称
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 添加可执行文件
add_executable(${TARGET} 
    main.cpp
)

# 链接库
target_link_libraries(${TARGET}
        ${SDL2_LIBRARIES}
        SDL2_image::SDL2_image
        SDL2_mixer::SDL2_mixer
        SDL2_ttf::SDL2_ttf
)