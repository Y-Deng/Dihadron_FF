cmake_minimum_required(VERSION 3.16)
project(BsplineInterpolation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Conan 导入
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake OPTIONAL)
if(EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
    include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
endif()

# 添加源码
file(GLOB BSPLINE_SOURCES "src/*.cc")
add_library(bspline STATIC ${BSPLINE_SOURCES}) 
target_include_directories(bspline PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# 添加对ROOT的依赖
include_directories(/usr/include/ROOT/)
link_directories(/usr/lib/x86_64-linux-gnu/)

# 依赖
find_package(Eigen3 REQUIRED)
find_package(GSL REQUIRED)
find_package(qcdnum REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

target_link_libraries(bspline
    PUBLIC Eigen3::Eigen GSL::gsl GSL::gslcblas
    Core Imt RIO Net Hist Graf Graf3d Gpad ROOTVecOps Tree TreePlayer
    Rint Postscript Matrix Physics MathCore Thread MultiProc ROOTDataFrame
    qcdnum::qcdnum
    m  # -lm
    dl # -ld
)

# 安装规则
install(TARGETS bspline EXPORT BsplineTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# CMake export 配置
install(EXPORT BsplineTargets
    FILE BsplineTargets.cmake
    NAMESPACE bspline::
    DESTINATION lib/cmake/Bspline
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/BsplineConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/cmake/BsplineConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/BsplineConfig.cmake"
    INSTALL_DESTINATION lib/cmake/Bspline
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/BsplineConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/BsplineConfigVersion.cmake"
    DESTINATION lib/cmake/Bspline
)

# 示例程序
add_executable(bspline_example examples/example_main.cc)
target_link_libraries(bspline_example PRIVATE bspline)

# 单元测试
enable_testing()
foreach(t initial_DiFF_z_Mh)
    add_executable(${t} tests/${t}.cc)
    target_link_libraries(${t} PRIVATE bspline)
    set_target_properties(${t} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
    )
    add_test(NAME ${t}  COMMAND ${CMAKE_BINARY_DIR}/bin/tests/${t})
endforeach()
