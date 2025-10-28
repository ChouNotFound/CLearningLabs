cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(CLearningLabs VERSION 1.0)

# 指定C语言标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置输出目录为build目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 自动收集所有源文件和头文件
file(GLOB_RECURSE CORE_SOURCES "core/**/*.c")
file(GLOB_RECURSE UTILS_SOURCES "utils/*.c")
file(GLOB_RECURSE CORE_HEADERS "core/**/*.h")
file(GLOB_RECURSE UTILS_HEADERS "utils/*.h")
file(GLOB_RECURSE INCLUDE_HEADERS "include/*.h")

# 包含目录
include_directories(.)
include_directories(core/**/)
include_directories(utils)
include_directories(include)

# 收集源文件和头文件
set(SOURCES 
    main.c
    ${CORE_SOURCES}
    ${UTILS_SOURCES}
)

set(HEADERS  # 新增头文件集合
    ${CORE_HEADERS}
    ${UTILS_HEADERS}
    ${INCLUDE_HEADERS}
)

# 添加可执行文件（包含头文件）
add_executable(CLearningLabs ${SOURCES} ${HEADERS})

# 设置可执行文件输出名称
set_target_properties(CLearningLabs PROPERTIES OUTPUT_NAME "CLearningLabs")