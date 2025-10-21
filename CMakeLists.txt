cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(CLearningLabs VERSION 1.0)

# 指定C语言标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置输出目录为build目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 自动收集core目录下的所有源文件和头文件
file(GLOB_RECURSE CORE_SOURCES "core/**/*.c")
file(GLOB_RECURSE CORE_HEADERS "core/**/*.h")

# 自动收集utils目录下的所有源文件和头文件
file(GLOB_RECURSE UTILS_SOURCES "utils/**/*.c")
file(GLOB_RECURSE UTILS_HEADERS "utils/**/*.h")

# 包含目录
include_directories(core/student_manager/include)
include_directories(utils/include)
include_directories(app)

# 收集源文件
set(SOURCES 
    app/main.c
    ${CORE_SOURCES}
    ${UTILS_SOURCES}
)

# 添加可执行文件
add_executable(CLearningLabs ${SOURCES})

# 设置可执行文件输出名称
set_target_properties(CLearningLabs PROPERTIES OUTPUT_NAME "CLearningLabs")