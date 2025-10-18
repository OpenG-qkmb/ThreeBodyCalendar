cmake_minimum_required(VERSION 3.15)
project(ThreeBodyCalendar
    VERSION 1.0.0
    DESCRIPTION "ThreeBodyCalendar"
    LANGUAGES CXX
)

# 基础配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 在Windows上设置一些默认选项
if(WIN32)
    # 使用Unicode
    add_definitions(-DUNICODE -D_UNICODE)
endif()

# 输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含目录
include_directories(include)

# 收集源文件
file(GLOB_RECURSE SOURCE_FILES 
    "src/*.cpp"
    "src/*.c"
)

# 创建可执行文件
add_executable(ThreeBodyCalendar ${SOURCE_FILES})

# 设置编译选项 - 必须在目标创建后调用
if(MSVC)
    # MSVC编译器选项
    target_compile_options(ThreeBodyCalendar PRIVATE 
        /W4           # 警告等级4
        /permissive-  # 标准一致性模式
    )
    
    # 在Debug模式禁用优化，Release模式启用优化
    target_compile_options(ThreeBodyCalendar PRIVATE 
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Release>:/O2>
    )
else()
    # GCC/Clang编译器选项
    target_compile_options(ThreeBodyCalendar PRIVATE 
        -Wall
        -Wextra
    )
endif()

# 设置链接选项
if(MSVC)
    target_link_options(ThreeBodyCalendar PRIVATE /DEBUG)
endif()

# 设置目标属性
set_target_properties(ThreeBodyCalendar PROPERTIES
    OUTPUT_NAME "ThreeBodyCalendar"
    VERSION ${PROJECT_VERSION}
)

# 为Visual Studio设置启动工作目录
if(MSVC)
    set_target_properties(ThreeBodyCalendar PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)"
    )
endif()

message(STATUS "Project configuration completed.")
message(STATUS "Number of source files: ${SOURCE_FILES}")
message(STATUS "Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")