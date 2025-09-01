cmake_minimum_required(VERSION 3.10)
project(MyCProject C)

# 设置 C 标准 (C11 或 C17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 包含目录
include_directories(include)

# 添加可执行文件
add_executable(my_program
    src/main.c
    src/utils.c
    src/algorithms.c
)

# 可选：安装规则
install(TARGETS my_program DESTINATION bin)
