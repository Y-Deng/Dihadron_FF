# 1. 指定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.15)

# 2. 项目信息
project(MyProject VERSION 1.0 LANGUAGES CXX)

# 3. 设置编译选项（可选）
set(CMAKE_CXX_STANDARD 20)            # 设置C++语言的标准    
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # 要求使用C++17标准
set(CMAKE_CXX_EXTENSIONS OFF)         # 关闭非标准扩展，以便于与其他库兼容

add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

find_package(Threads REQUIRED)

include_directories(/usr/include/)
include_directories(/usr/include/ROOT/)
link_directories(/usr/lib/)
link_directories(/usr/lib/x86_64-linux-gnu/)

file(GLOB_RECURSE SOURCES *.cc)

# 4. 添加源文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 5. 链接库（如需要）
target_link_libraries(${PROJECT_NAME}
    Core Imt RIO Net Hist Graf Graf3d Gpad ROOTVecOps Tree TreePlayer
    Rint Postscript Matrix Physics MathCore Thread MultiProc ROOTDataFrame
    m  # -lm
    dl # -ld
    # gfortran # -lgfortran
    # quadmath # -lquadmath
    QCDNUM
    LHAPDF
    gsl
    gslcblas
)

# # 6. 包含目录
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     BUILD_RPATH "/public/home/dengyj/anaconda3/envs/root_environment/lib/"
# )
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)