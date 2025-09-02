cmake_minimum_required(VERSION 3.10)
project(s604-bintree_queue_stack)

# 设置 C 标准（如果是 C 项目）
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 直接添加源文件，而不是使用 add_subdirectory
#file(GLOB SOURCES "src/*.c")  # 如果是 C 文件
file(GLOB SOURCES "src/*.cpp") # 如果是 C++ 文件

# 或者明确列出源文件
#set(SOURCES
#    src/main.c
#    src/tree.c
#    src/queue.c
# 添加其他源文件
#)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
